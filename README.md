# Hash-tree-implementation

This project is based on the associative rule mining algorithms implemented using a hash tree. The datset is a collection of information about U.S. senators and their corresponding votes for 16 key issues. The dataset also contains the political party that each senator is affiliated with. The votes are binary- Yes or No and each line in the dataset corresponds to one senator. 

The implementation of this project gives vital information hidden within the dataset. Rules have been mined by using the hash tree data structure and the frequent itemset generation has been carried out by the Apriori algorithm. Confidence based pruning has been carried out to give the user the results they desire.


Dataset:
vote.arff

Files such as attributes.txt, data_aftr_preprocess_num.txt and data_aftr_preprocess_string.txt have been created after processing vote.arff 
for programming simplicity.

Code:
DM.cpp

Output File:
Output.txt

By changing values inside the cpp files for support count and confidence, the output files will generate different results.

Link for actual dataset:
http://tunedit.org/repo/UCI/vote.arff
