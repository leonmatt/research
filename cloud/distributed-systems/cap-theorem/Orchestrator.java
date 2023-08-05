/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

import java.util.*;

public class Orchestrator
{

    public int numberOfNodes;
    public int capQualities;
    private Vector<Node> nodes;

    public Orchestrator(int numNodes, int qualitiesChoice)
    {

        // Set up the orchestator with the nodes
        setupOrchestrator(numNodes, qualitiesChoice);

        System.out.println("Finished setting up the Orchestrator\n");

    }

    public void startOrchestrator()
    {

        switch(capQualities) {
            case 1:
                System.out.println("Running with Consistency and Availability\n");
                break;
            case 2:
                System.out.println("Running with Consistency and Partitioning\n");
                break;
            case 3:
                System.out.println("Running with Availability and Partitioning\n");
                break;
        }

        System.out.println("Starting the Orchestrator\n");

        Random rng = new Random();
        int newValue;

        while(true) {

            // Consistency and Availability
            if (capQualities == 1) {

                newValue = rng.nextInt(100);
                System.out.println("Writing " + newValue + " to the Nodes\n");
                for (int i = 0; i < numberOfNodes; i++)
                    nodes.get(i).write(newValue);
                
                newValue = rng.nextInt(numberOfNodes);

                System.out.println("Value stored in Node " + newValue + " is: " + nodes.get(newValue).read() + "\n");

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {}

            }

        }

    }

    private void setupOrchestrator(int numNodes, int qualities)
    {

        nodes = new Vector<Node>();

        for(int i = 0; i < numNodes; i++)
            nodes.add(new Node());

        System.out.println("We added " + numNodes + " nodes to the system\n\n");

        numberOfNodes = numNodes;
        capQualities = qualities;

    }

}