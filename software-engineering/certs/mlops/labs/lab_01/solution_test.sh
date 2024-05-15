#!/bin/bash

# Open port 5000 on the system for the lab
sudo ufw allow 5000

# Start the FastAPI server
cd sample
python serve.py > /dev/null 2>&1 &
server_pid=$!
sleep 5
printf "\nStarted Server, now posting POST requests..\n"


# Run curl commands for not requiring and requiring maintenance
printf "\n\n\nPosting Hydraulic Pressure == 2000\n\n\n"
curl -X POST http://127.0.0.1:5000/maintenance -H 'Content-Type: application/json' -d '{"hydraulic_pressure":2000}'
sleep 1
printf "\n\n\nPosting Hydraulic Pressure == 2001\n\n\n"
curl -X POST http://127.0.0.1:5000/maintenance -H 'Content-Type: application/json' -d '{"hydraulic_pressure":2001}'
printf "\n\n\n"

sleep 1

printf "\n\n\nPosting help to supportbot\n\n\n"
curl -X POST http://127.0.0.1:5000/supportbot -H 'Content-Type: application/json' -d '{"input_string": "help"}'
sleep 1
printf "\n\n\nPosting help not needed to supportbot\n\n\n"
curl -X POST http://127.0.0.1:5000/supportbot -H 'Content-Type: application/json' -d '{"input_string": "help not needed"}'
printf "\n\n\n"

# Stop the server
kill $server_pid