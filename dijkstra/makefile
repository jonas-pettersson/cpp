build : Dijkstra.cpp;
	g++ -g -Wall -o DijkstraHeap DijkstraHeap.cpp
run : dijkstraData.txt;
#run : test_case_4.txt
#	./DijkstraHeap 1 14 test_case_4.txt
	./DijkstraHeap 1 200 dijkstraData.txt | awk 'NR==7 || NR==37 || NR==59 || NR==82 || NR==99 || NR==115 || NR==133 || NR==165 || NR==188 || NR==197' | cut -f3 -d' '
