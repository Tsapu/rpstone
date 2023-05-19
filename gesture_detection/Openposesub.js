//
// Parses the hand keypoints and returns best guess for the gesture
//

const { GestureEstimator } = require('fingerpose');
const { RockGesture, PaperGesture, ScissorsGesture } = require('./Gestures');

const knownGestures = [RockGesture, PaperGesture, ScissorsGesture];
const gestureEstimator = new GestureEstimator(knownGestures);

// import ROSLIB from 'roslib';
const ROSLIB = require('roslib');

const ros = new ROSLIB.Ros({
	url: 'ws://localhost:9090',
	name: 'rpsjs_node'
});

const listener = new ROSLIB.Topic({
	ros: ros,
	name: '/frame',
	messageType: 'ros_openpose/Frame',
});

// Create a publisher for the rps_gestures topic
const publisher = new ROSLIB.Topic({
  ros: ros,
  name: '/rps_gestures',
  messageType: 'rpstone/Gesture'
});


const prepMsg = (gesture) => {
	const message = new ROSLIB.Message({
		player1_gesture: '',
		player2_gesture: ''
	});
	message.player1_gesture = gesture;
	return message;
}

listener.subscribe((message) => {
	const { persons } = message;
	if (persons.length === 0) {
		return;
	}

	const { rightHandParts: hand1 } = persons[0];
	const { leftHandParts: hand2 } = persons[0]; // this would be replaced with the person #2 right hand

	const gesture = predictGesture(hand2);

	if (gesture !== '') {
		console.log(gesture);
		const message = prepMsg(gesture);
		publisher.publish(message);
	}
});

const predictGesture = (hand) => {

	const keypoints = extractLandmarks(hand);
	if (keypoints.length === 0) { 
		return '';
	}
	console.log(keypoints)

	const gestureEstimations = gestureEstimator.estimate(
		keypoints, 9 // minimum confidence
	);

	if(gestureEstimations.gestures.length > 0) {
	
		// this will reduce an array of results to a single value
		// containing only the gesture with the highest score
		const gestureResult = gestureEstimations.gestures.reduce((p, c) => { 
				return (p.confidence > c.confidence) ? p : c;
		});

		return gestureResult.name;
	}
	return '';
}

function extractLandmarks(hand) {
	const landmarks = [];
	if (hand !== undefined) {
		hand.forEach((part) => {
			const { pixel } = part;
			const { x, y } = pixel;
			landmarks.push([x, y, 0]);
		});
	}
	return landmarks
}