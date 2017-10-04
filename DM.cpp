#include <bits/stdc++.h>

#define ll long long
#define ld long double
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define IOS ios::sync_with_stdio(false)
#define vi vector < ll >
#define sort(a) sort(a.begin(),a.end())
#define reverse(a)  reverse(a.begin(),a.end())
#define pb push_back
#define mp make_pair

using namespace std;

ll idx;
ll k=1;
ld minsup=0.5;
ld minconf=0.9;

map<ll,string> ID_string;
map<string,ll> string_ID;
map<set<ll>,ll>	support_count;
map<set<ll>,ll> leaf_supp_cnt;
string attribute_name[60];
vector < set<set <ll> > > freq_items;

ifstream input_file;
ofstream output_file1;
ofstream output_file2;

struct node
{
	ll curr_height;
	bool is_leaf;
	vector< set< ll > > v;
	node *link0,*link1,*link2,*link3;
};

struct node* root=NULL;

bool check_candidate(set<ll> ck)
{
	vi check;
	for(set<ll>:: iterator it=ck.begin();it!=ck.end();it++)	check.pb(*it);

	rep(i,0,check.size())
	{
		if(check[i]==2)
		{
			vi:: iterator itr=lower_bound(check.begin(),check.end(),1);
			if(itr!=check.end()) if(*itr==1)	return false;
		}
		else if(check[i]==1)
		{
			vi:: iterator itr=lower_bound(check.begin(),check.end(),2);
			if(itr!=check.end()) if(*itr==2)	return false;
		}
		else
		{
			ll rem=check[i]%3;
			if(rem==0)
			{
				vi:: iterator itr=lower_bound(check.begin(),check.end(),check[i]+1);
				if(itr!=check.end()) if(*itr==check[i]+1)	return false;
				itr=lower_bound(check.begin(),check.end(),check[i]+2);
				if(itr!=check.end()) if(*itr==check[i]+2)	return false;
			}
			else if(rem==1)
			{
				vi:: iterator itr=lower_bound(check.begin(),check.end(),check[i]+1);
				if(itr!=check.end()) if(*itr==check[i]+1)	return false;
			}
		}
	}
	return true;
}

struct node * new_node(ll cur_ht)
{
   	struct node *temp  = new node;
   	temp->is_leaf=true;
   	temp->curr_height=cur_ht+1;

   	temp->link0=NULL;
   	temp->link1=NULL;
   	temp->link2=NULL;
   	temp->link3=NULL;
    return temp;
}

void destroy(struct node*& Node)
{
    if(Node!=NULL)
    {
        destroy(Node->link0);
        destroy(Node->link1);
        destroy(Node->link2);
        destroy(Node->link3);
        Node->v.clear();
        delete Node;
        Node=NULL;
    }
}

void insert_into_hashtree(struct node*& Node,set<ll> cur_set,ll hash_pos)
{
	if(!Node->is_leaf)
	{
		vi temp_v;
		for(set<ll>:: iterator it=cur_set.begin();it!=cur_set.end();it++)	temp_v.pb(*it);
		ll hash_val=temp_v[hash_pos]%4;
		if(hash_val==0)
		{
			if(Node->link0==NULL)
			{
				Node->link0=new_node(Node->curr_height);
				Node->link0->v.pb(cur_set);
			}

			else if(!Node->link0->is_leaf)
			{
				insert_into_hashtree(Node->link0,cur_set,hash_pos+1);
			}

			else if(Node->link0->v.size()==3 && cur_set.size() > Node->link0->curr_height)
			{
				vector<set< ll > > store;
				store.pb(cur_set);
				rep(i,0,Node->link0->v.size())	store.pb(Node->link0->v[i]);
				Node->link0->is_leaf=false;
				Node->link0->v.clear();

				rep(i,0,store.size())
				{
					insert_into_hashtree(Node->link0,store[i],hash_pos+1);
				}
			}

			else    Node->link0->v.pb(cur_set);
		}

		else if(hash_val==1)
		{
			if(Node->link1==NULL)
			{
				Node->link1=new_node(Node->curr_height);
				Node->link1->v.pb(cur_set);
			}

			else if(!Node->link1->is_leaf)
			{
				insert_into_hashtree(Node->link1,cur_set,hash_pos+1);
			}

			else if(Node->link1->v.size()==3 && cur_set.size() > Node->link1->curr_height)
			{
				vector<set< ll > > store;
				store.pb(cur_set);
				rep(i,0,Node->link1->v.size())	store.pb(Node->link1->v[i]);
				Node->link1->is_leaf=false;
				Node->link1->v.clear();

				rep(i,0,store.size())
				{
					insert_into_hashtree(Node->link1,store[i],hash_pos+1);
				}
			}

			else    Node->link1->v.pb(cur_set);

		}

		else if(hash_val==2)
		{
			if(Node->link2==NULL)
			{
				Node->link2=new_node(Node->curr_height);
				Node->link2->v.pb(cur_set);
			}

			else if(!Node->link2->is_leaf)
			{
				insert_into_hashtree(Node->link2,cur_set,hash_pos+1);
			}

			else if(Node->link2->v.size()==3 && cur_set.size() > Node->link2->curr_height)
			{
				vector<set< ll > > store;
				store.pb(cur_set);
				rep(i,0,Node->link2->v.size())	store.pb(Node->link2->v[i]);
				Node->link2->is_leaf=false;
				Node->link2->v.clear();

				rep(i,0,store.size())
				{
					insert_into_hashtree(Node->link2,store[i],hash_pos+1);
				}
			}

			else    Node->link2->v.pb(cur_set);
		}

		else
		{
			if(Node->link3==NULL)
			{
				Node->link3=new_node(Node->curr_height);
				Node->link3->v.pb(cur_set);
			}

			else if(!Node->link3->is_leaf)
			{
				insert_into_hashtree(Node->link3,cur_set,hash_pos+1);
			}

			else if(Node->link3->v.size()==3 && cur_set.size() > Node->link3->curr_height)
			{

				vector<set< ll > > store;
				store.pb(cur_set);
				rep(i,0,Node->link3->v.size())	store.pb(Node->link3->v[i]);
				Node->link3->is_leaf=false;
				Node->link3->v.clear();

				rep(i,0,store.size())
				{
					insert_into_hashtree(Node->link3,store[i],hash_pos+1);
				}
			}
			else
				Node->link3->v.pb(cur_set);
		}
	}
}

void pass_into_hashtree(set<ll> cur_set,struct node*& Node,ll hash_pos)
{
	if(Node==NULL) return;
    if(!Node->is_leaf)
    {
        vi temp_v;
		for(set<ll>:: iterator it=cur_set.begin();it!=cur_set.end();it++)	temp_v.pb(*it);
		ll hash_val=temp_v[hash_pos]%4;
        if(hash_val==0) pass_into_hashtree(cur_set,Node->link0,hash_pos+1);
        else if(hash_val==1) pass_into_hashtree(cur_set,Node->link1,hash_pos+1);
        else if(hash_val==2) pass_into_hashtree(cur_set,Node->link2,hash_pos+1);
        else if(hash_val==3) pass_into_hashtree(cur_set,Node->link3,hash_pos+1);
    }
    else
    {
        rep(i,0,Node->v.size())
        {
            set<ll> diff;
            set_difference(cur_set.begin(),cur_set.end(),Node->v[i].begin(),Node->v[i].end(),inserter(diff, diff.end()));
            if(diff.empty())    leaf_supp_cnt[Node->v[i]]++;
        }
    }
}

void generate_subset(vi v,ll k)
{
    ll sz=v.size();
    if(sz<k) return ;
    rep(i,0,(1<<sz))
    {
        set<ll> s;
        ll cnt=__builtin_popcountll(i);
        if(cnt!=k) continue;
        rep(j,0,sz) if(i&(1<<j)) s.insert(v[j]);
        pass_into_hashtree(s,root,0LL);
    }
}

set<set< ll > > freq_gen(set<set< ll> > cand_k, ll sz_subset)
{
	root=new node;
	root->is_leaf=false;

	root->curr_height=0;
	root->link0=NULL;
	root->link1=NULL;
	root->link2=NULL;
	root->link3=NULL;
	for(set<set< ll > >:: iterator it=cand_k.begin();it!=cand_k.end();it++)		insert_into_hashtree(root,*it,0);

    input_file.open("data_aftr_preprocess_num.txt");
    while(input_file)
	{
		string str;
		vi vote_data;
		if(!getline(input_file,str))	break;
		istringstream strstream(str);
		while(strstream)
		{
			string s;
			if(!getline(strstream,s,','))	break;
            ll z=atoi(s.c_str());
            vote_data.pb(z);
		}
        generate_subset(vote_data,sz_subset);
	}
	input_file.close();

    set<set < ll > > frequent;
    for(map <set<ll>,ll>::iterator it=leaf_supp_cnt.begin();it!=leaf_supp_cnt.end();it++)
    {
        ld support=it->second/435.0;
        if(support>=minsup)
        {
            frequent.insert(it->first);
            support_count[it->first]=it->second;
        }
    }
    return frequent;
}


set<set< ll > > apriori_gen_k(set<set< ll > > freq_k_minus_1)
{
	set<set< ll > > cand_k;
	for(set<set< ll > >:: iterator it1=freq_k_minus_1.begin();it1!=freq_k_minus_1.end();it1++)
	{
		set<set< ll > >:: iterator it2=it1;
		it2++;
		for(;it2!=freq_k_minus_1.end();it2++)
		{
			set<ll> temp_1=*it1;
			set<ll> temp_2=*it2;
			set<ll> diff;
			set<ll> :: iterator last_itr=temp_1.end();
			last_itr--;

			ll L1=*last_itr;
			temp_1.erase(last_itr);

			last_itr=temp_2.end();
			last_itr--;

			ll L2=*last_itr;
			temp_2.erase(last_itr);

			set_difference(temp_1.begin(), temp_1.end(), temp_2.begin(), temp_2.end(),inserter(diff, diff.end()));
			if(diff.empty())
			{
				temp_2.insert(L2);
				temp_2.insert(L1);
				if(check_candidate(temp_2))		cand_k.insert(temp_2);
			}
		}
	}
	return cand_k;
}

set<set< ll > > apriori(set<set< ll> > cand)
{
	set<set< ll > > candidates;
	candidates= apriori_gen_k(cand);
	return candidates;
}

ll cnt=1;

void rule_generate(set<ll> frequent,set< set <ll> > rule_consequent,ll sz_set,ll consequent_sz)
{
	if(sz_set == consequent_sz)		return;

	set<set<ll> > remove;
	set< set<ll> >:: iterator it=rule_consequent.begin();
	ll size = sz_set;
	while(it!=rule_consequent.end())
	{
		set<ll> temp=*it,diff;
		set_difference(frequent.begin(), frequent.end(), temp.begin(), temp.end(),inserter(diff, diff.end()));


		if( (ld) support_count[frequent] / (ld) support_count[diff] >= minconf)
		{
			output_file1<<cnt++<<" : ";
			for(set<ll>:: iterator itr=diff.begin();itr!=diff.end();itr++)
			{
				map<ll,string>:: iterator itrrr=ID_string.find(*itr);
				output_file1<<itrrr->second;	output_file1<<", ";
			}
			output_file1<<" ---> ";
			for(set<ll>::iterator itr=temp.begin();itr!=temp.end();itr++)
			{
				map<ll,string>:: iterator itrrr=ID_string.find(*itr);
				output_file1<<itrrr->second;	output_file1<<", ";
			}
			output_file1<<"\n\n";
		}

		else
		{
			remove.insert(*it);
		}
		it++;
	}
	it=remove.begin();
	set< set<ll> >:: iterator itr=rule_consequent.begin();
	for(;it!=remove.end();it++)
	{
		for(;itr!=rule_consequent.end();itr++)
			if(*itr==*it)	rule_consequent.erase(itr);
	}

	rule_consequent=apriori_gen_k(rule_consequent);
	if(rule_consequent.size()==0)	return;
	rule_generate(frequent,rule_consequent,sz_set,consequent_sz+1);
}




int main()
{
    IOS;
    cout<<setiosflags(ios::fixed|ios::showpoint)<<setprecision(10);
	map<string,ll> data_table;
	input_file.open("attributes.txt");
	while(input_file)
	{
		string str;
		if(!getline(input_file,str))	break;
		attribute_name[idx++]=str;
		data_table[str]=0;
	}
	input_file.close();

    idx=1;
	for(map<string,ll>:: iterator it=data_table.begin();it!=data_table.end();it++)
	{
		ID_string[idx]=it->first;
		string_ID[it->first]=idx;
		idx++;
	}

    input_file.open("vote.arff");
    output_file1.open("data_aftr_preprocess_num.txt");
    output_file2.open("data_aftr_preprocess_string.txt");

    idx=0;
	while(input_file)
	{
		string str;
		set<ll> temp_id;
		set <string> temp_name;
		while(getline(input_file,str))
		{
			idx=0;
			rep(i,0,str.size())
			{
				if(str[i]=='n')
	            {
	                string ssss=attribute_name[3*idx+1];
	                map<string,ll>:: iterator it=string_ID.find(ssss);
	                temp_id.insert(it->second);
	                temp_name.insert(ssss);
	                idx++;

	            }
	            else if(str[i]=='y')
	            {
	                string ssss=attribute_name[3*idx];
	                map<string,ll>:: iterator it=string_ID.find(ssss);
	                temp_id.insert(it->second);
	                temp_name.insert(ssss);
	                idx++;

	            }
				else if(str[i]=='?')
	            {
	                string ssss=attribute_name[3*idx+2];
	                map<string,ll>:: iterator it=string_ID.find(ssss);
	                temp_id.insert(it->second);
	                temp_name.insert(ssss);
	                idx++;

	            }
				else if(str[i]=='d')
	            {
	                temp_id.insert(1);
	                temp_name.insert("Democrat");
	                break;

	            }
				else if(str[i]=='r')
	            {
	                temp_id.insert(2);
	                temp_name.insert("Republican");
	                break;
	            }
			}
			for(set<ll>:: iterator it=temp_id.begin();it!=temp_id.end();it++)   {   output_file1<<*it;  output_file1<<",";    }
	        for(set<string>:: iterator it=temp_name.begin();it!=temp_name.end();it++)   {   output_file2<<*it;  output_file2<<",";    }
	        output_file1<<'\n';
	        output_file2<<'\n';
	        temp_id.clear();
	        temp_name.clear();
		}
	}
	input_file.close();
	output_file1.close();
    output_file2.close();

	input_file.open("data_aftr_preprocess_string.txt");
	while(input_file)
	{
		string str;
		while(getline(input_file,str))
		{
			ll st=0,en=0;
			while(en!=str.size())
			{
				for(;str[en]!=',';en++);
				string s=str.substr(st,en-st);
				data_table[s]++;
				en++;
				st=en;
			}
		}
	}
	input_file.close();

	set<set<ll> > f1;
	for(map<string,ll> ::iterator it=data_table.begin();it!=data_table.end();it++)
	{
		ld support=it->second/435.0;
		if(support>=minsup)
		{
			set<ll> temp;
			for(map<ll,string>:: iterator itr=ID_string.begin();itr!=ID_string.end();itr++)
            {
                if(it->first==itr->second)  temp.insert(itr->first);
            }
			f1.insert(temp);
            support_count[temp]=it->second;
		}
	}
    freq_items.pb(f1);

    ll k=1;
    while(true)
    {
     	set<set< ll> > ck= apriori(freq_items[k-1]);
        if(ck.empty())	break;
        k=k+1;
        set<set< ll > > fk = freq_gen(ck,k);
        if(fk.empty())  break;
        freq_items.pb(fk);
        leaf_supp_cnt.clear();
        destroy(root);
    }

	output_file1.open("Output.txt");
    for(ll i=1;i<freq_items.size();i++)
    {
    	for(set<set<ll> >:: iterator it=freq_items[i].begin();it!=freq_items[i].end();it++)
    	{
    		set<ll> frequent=*it;
    		set<set<ll > > rule_consequent;
    		for(set<ll>:: iterator itr=frequent.begin();itr!=frequent.end();itr++)
    		{
    			set<ll> temp;
    			temp.insert(*itr);
    			rule_consequent.insert(temp);
    		}
    		rule_generate(frequent,rule_consequent,frequent.size(),1);
    		rule_consequent.clear();
    	}
    }
    output_file1.close();
    return 0;
}
