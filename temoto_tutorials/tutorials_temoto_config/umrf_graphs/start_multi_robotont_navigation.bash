TEMOTO_NAMESPACE=$1

# Initialize the robots
rosrun temoto_action_engine umrf_graph_publisher robotont_sim_1_initialize.umrfg.json $TEMOTO_NAMESPACE
rosrun temoto_action_engine umrf_graph_publisher robotont_sim_2_initialize.umrfg.json $TEMOTO_NAMESPACE

sleep 7

# Run the cyclical navigation graphs
rosrun temoto_action_engine umrf_graph_publisher robotont_sim_1_nav_cycle.umrfg.json $TEMOTO_NAMESPACE
sleep 5
rosrun temoto_action_engine umrf_graph_publisher robotont_sim_2_nav_cycle.umrfg.json $TEMOTO_NAMESPACE
