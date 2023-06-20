#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

class GameLogic
{
public:
    GameLogic()
    {
        sub_ = nh_.subscribe("winning_player", 1, &GameLogic::sub_callback, this);
        pub1_ = nh_.advertise<geometry_msgs::Twist>("robotont/robotont_sim_1/cmd_vel", 1);
        pub2_ = nh_.advertise<geometry_msgs::Twist>("robotont/robotont_sim_2/cmd_vel", 1);
    }

    void sub_callback(const std_msgs::String::ConstPtr& msg)
    {
        if (msg->data == "player1")
        {
            twist1_cmd.linear.x = 0.1;
            twist2_cmd.linear.x = 0.0;

            pub1_.publish(twist1_cmd);
            pub2_.publish(twist2_cmd);
        }

        else if (msg->data == "player2")
        {
            twist1_cmd.linear.x = 0.0;
            twist2_cmd.linear.x = 0.1;

            pub1_.publish(twist1_cmd);
            pub2_.publish(twist2_cmd);
        }

    }


private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher pub1_;
    ros::Publisher pub2_;

    geometry_msgs::Twist twist1_cmd;
    geometry_msgs::Twist twist2_cmd;

};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "TaGameLogic");
    GameLogic game_logic;

    ros::spin();
    return 0;


}