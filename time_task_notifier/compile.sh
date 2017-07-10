# TODO killing of previous tasks for fresh start IF code modified.
# kill -9 PID_OF_executor. To be done before starting executor
# ps -eaf | grep task_server | awk '{print $2}' | xargs kill -9

rm -rf task_server notify_me my_action
cc -o my_action    my_action.c    -lrt
cc -o task_server  task_server.c  -lrt
cc -o notify_me    notify_me.c    -lrt
