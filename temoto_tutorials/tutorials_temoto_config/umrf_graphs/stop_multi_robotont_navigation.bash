TEMOTO_NAMESPACE=$1

rostopic pub -1 /broadcast_stop_umrf_graph temoto_action_engine/BroadcastStopUmrfGraph "umrf_graph_name: 'robotont_sim_1_nav_cycle'
targets:
  -
    "$TEMOTO_NAMESPACE""

rostopic pub -1 /broadcast_stop_umrf_graph temoto_action_engine/BroadcastStopUmrfGraph "umrf_graph_name: 'robotont_sim_2_nav_cycle'
targets:
  -
    "$TEMOTO_NAMESPACE""

sleep 5

rostopic pub -1 /broadcast_stop_umrf_graph temoto_action_engine/BroadcastStopUmrfGraph "umrf_graph_name: 'robotont_sim_1_initialize'
targets:
  -
    "$TEMOTO_NAMESPACE""

sleep 5

rostopic pub -1 /broadcast_stop_umrf_graph temoto_action_engine/BroadcastStopUmrfGraph "umrf_graph_name: 'robotont_sim_2_initialize'
targets:
  -
    "$TEMOTO_NAMESPACE""