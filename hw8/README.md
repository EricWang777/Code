Bingtang Wang
8675881382
Hw 8 
Q1 and Q2 are in the Q1Q2.JPG file
1k, 1w, 10w, 100w are the files with
1000, 10000, 100000, 1000000 strings 


Part 4

1. 1k, 1w, 10w, 100w
2. 
-------------------------------------------
input size | probing method | time used(s) |
-------------------------------------------
  1,000          linear        0.01444
-------------------------------------------
  1,000          quadratic     0.01440
-------------------------------------------
  1,000          double        0.02822
-------------------------------------------
  10,000         linear        0.13467
-------------------------------------------
  10,000         quadratic     0.13488
-------------------------------------------
  10,000         double        0.25088
-------------------------------------------      
  100,000        linear        1.23796
-------------------------------------------
  100,000        quadratic     1.22194
-------------------------------------------
  100,000        double        2.31217
------------------------------------------- 
  1,000,000      linear        17.076
-------------------------------------------
  1,000,000      quadratic     16.7719
-------------------------------------------
  1,000,000      double        31.2427
------------------------------------------- 
Please see Plot.png to see the plot!!

3. Linear and quadratic probing doesn't need much time to calcuate the 
   number of shifting slots. However, double hash probing needs to do another
   hash function which takes some time to calcutate the result of string. 
   Accordingly, linear and double uses approximately same time while double 
   hashing takes longer

4. 
	a) VS. unsorted list
		hash table will be slower in inserting but absolutely faster in finding.
		hash table runtime for finding is O(1) while unsorted list is O(n)
	b) VS. sorted list
		Same as unsorted list. However, the runtime for unsrted list to find is 
		O(logn), but still slower than that of hash table
	c) VS. Binary search tree, non-rotating variety
		Probably hash table is slower in inserting. But still faster in finding while
		bst takes logn. Moreover, while it is non-rotating variety, the tree could
		possibly becomes heavily unbalanced and has runtime between logn and n
	d) VS. AVL
		Same as BST. However, while inserting, it may takes same or more time 
		to do rotation. While the finding gurantees to be logn, it is still 
		slower than hash table, which is O(1)
