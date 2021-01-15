

	4			5 			6	  		7
	 
	 	2(dist = '2')		3(dist = '1')

					1
	
	2 is connected to node 4,5,6,7 with edge weight 1
	3 is also connected to node 4,5,6,7 with edge weight 100
	
	queue<dist, vertex>, distance represented with '' marks
	1) we pop 1 from queue and push {'1', 3} and push {'2', 2}
	2) we now pop vertex 3 and dilute distance to node 4,5,6,7 with 101 and push {'101', 4},{'101', 5},{'101', 6},{'101', 7} into queue
	3) we pop vertex 2 and again dilute the distance to node 4,5,6,7 and push {'3', 4}, {'3', 5}, {'3', 6}, {'3', 7} to queue
	
	we notice that we now have useless copy of {'101', 4}... in our queue, and when we pop it we will again itreate over neighbours of 4
	to dilute them, which are already diluted by {'3', 4}
