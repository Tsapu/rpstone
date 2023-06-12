#!/usr/bin/env node

// import '@tensorflow/tfjs-backend-webgl';

// import the FingerPose gesture estimator + our predefined gestures
// import { GestureEstimator } from 'fingerpose';
// import { RockGesture, PaperGesture, ScissorsGesture } from './Gestures';

const { GestureEstimator } = require('fingerpose');
const { RockGesture, PaperGesture, ScissorsGesture } = require('./Gestures');

const knownGestures = [RockGesture, PaperGesture, ScissorsGesture];
const gestureEstimator = new GestureEstimator(knownGestures);

// import ROSLIB from 'roslib';
const ROSLIB = require('roslib');

let ros;

const establishConnection = () => {
  ros = new ROSLIB.Ros({
		url: 'ws://localhost:9090',
		name: 'rpsjs_node'
	});
	ros.on('connection', () => {
    console.log('Connected to ROS');
    // Add your ROS-related code here
  });
  ros.on('error', (error) => {
    console.error('Error connecting to ROS');
    // Retry the connection after a certain delay
    setTimeout(establishConnection, 1000);
  });
  ros.on('close', () => {
    console.log('Connection to ROS closed');
    // Retry the connection after a certain delay
    setTimeout(establishConnection, 1000);
  });
}
establishConnection();

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


const prepMsg = (gesture1, gesture2='None') => {

	const message = new ROSLIB.Message({
		player1_gesture: '', // player one is always assumed to be on the left
		player2_gesture: '' // player two is on the right
	});
	//message.header.stamp = new ROSLIB.Time();
	message.player1_gesture = gesture1;
	message.player2_gesture = gesture2;
	return message;
}

listener.subscribe((message) => {
	const { persons } = message;
	// assume two persons only, ignore everything else, hope nothing comes from the background
	let msg, gesture1, gesture2, hand1, hand2, x_pos1, x_pos2, hand1_leftest;

	if (persons.length === 0) {
		return;
	} else if (persons.length === 1) {
	  hand1 = persons[0].rightHandParts;
		hand2 = persons[0].leftHandParts;
		gesture1 = predictGesture(hand1);
		gesture2 = predictGesture(hand2);
		msg = prepMsg(gesture1, gesture2);
		if (gesture1 !== '' || gesture2 !== '') {
			publisher.publish(msg);
		}
		
	} else if (persons.length === 2) {
	  hand1 = persons[0].rightHandParts;
		hand2 = persons[1].rightHandParts;
	  
		x_pos1 = hand1.reduce((sum, pixel) => sum + pixel.x, 0) / hand1.length;
		x_pos2 = hand2.reduce((sum, pixel) => sum + pixel.x, 0) / hand2.length;

		gesture1 = predictGesture(hand1);
		gesture2 = predictGesture(hand2);

		hand1_leftest = (x_pos2 > x_pos1)

		if (hand1_leftest) {
			msg = prepMsg(gesture1, gesture2);
		} else {
			msg = prepMsg(gesture2, gesture1);
		}
		if (gesture1 !== '' || gesture2 !== '') {
			publisher.publish(msg);
		}
	}

	// if (gesture !== '') {
	// 	console.log(gesture);
	// 	const message = prepMsg(gesture);
	// 	publisher.publish(message);
	// }
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
		
		// logic for publishing a new gesture
		// ...

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

function calculateAverageYPixelCoordinates(handPosePixels) {
  handPosePixels.length ? handPosePixels.reduce((sum, pixel) => sum + pixel.y, 0) / handPosePixels.length : 0;
}