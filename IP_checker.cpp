#include<bits/stdc++.h>

using namespace std;

class IP 
{
private:
    set<string> ip4_list;
    set<string> ip6_list;
    int ip4_count{0};
    int ip6_count{0};
    int invalid_ip_count{0};
    
protected:
	
	/*This function checks if provided string satisfies conditions of IPv4 address*/
bool validate_IP4(string s)
{
    int count = 0;
    for(int loop = 0; loop<s.size(); loop++)
	{
	   if('.' == s[loop])
       count++;
	}
    if(3 != count)
		return false;
	vector<string> tokens;
	
	stringstream check1(s);
	string intermediate;
	
	while(getline(check1, intermediate, '.'))
	{
		tokens.push_back(intermediate);
	}
	if(4 != tokens.size())
      return false;
    for(int loop = 0; loop < tokens.size(); loop++)
	{
      int num = 0;
	  if("0" == tokens[loop])
		  continue;
	  if(0 == tokens[loop].size())
          return false;
      for(int loop1 = 0; loop1 < tokens[loop].size(); loop1++)
	  {
       if('9' < tokens[loop][loop1] || tokens[loop][loop1] < '0')
          return false;
          num *= 10;
          num += tokens[loop][loop1] - '0';
        if(0 == num)
           return false;
	  }
    if(num > 255 || num < 0)
      return false;
	}
	return true;
}
/*This function checks if provided string satisfies conditions of Hexadecimal value*/
bool validate_Hex(string s)
{
	int len = s.length();
	for(int loop = 0; loop < len; loop++)
	{
		char temp = s[loop];
		if(('0' > temp || temp > '9') && ('A' > temp || temp > 'F') && ('a' > temp || temp > 'f'))
			return false;
	}
	return true;
}
/*This function checks if provided string satisfies conditions of IPv6 address*/
bool validate_IP6(string s)
{
	int count = 0;
	for(int i = 0; i < s.size(); i++)
	{
		if(':' == s[i])
			count++;
	}
	if(7 != count)
		return false;
	vector<string> tokens;
	stringstream check1(s);
	string intermediate;
	
	while(getline(check1, intermediate, ':'))
	{
		tokens.push_back(intermediate);
	}
	if(8 != tokens.size())
		return false;
	
	for(int i = 0; i < tokens.size(); i++)
	{
		int len = tokens[i].size();
		if(!validate_Hex(tokens[i]) || len > 4 || len < 1)
			return false;
	}
	return true;
}
    
    public:
    void get_total_ip4_count()
    {
        cout<<"Total IPv4 address count: "<<ip4_count<<endl;
    }
    void get_unique_ip4_count()
    {
        cout<<"Unique IPv4 address count: "<<ip4_list.size()<<endl;
    }
    void get_total_ip6_count()
    {
        cout<<"Total IPv6 address count "<<ip6_count<<endl;
    }
    void get_unique_ip6_count()
    {
        cout<<"Unique IPv6 address count: "<<ip6_list.size()<<endl;
    }
    void get_invalid_ip_count()
    {
        cout<<"Invalid IP address count: "<<invalid_ip_count<<endl;
    }

/*This function updates counter values in the class instance*/
void validate_ip(string input)
{
	if(validate_IP4(input))
	{
	    ip4_list.insert(input);
	    ip4_count++;
	}
	else if(validate_IP6(input))
	{
	    ip6_list.insert(input);
	    ip6_count++;
	}
	else
	{
	    invalid_ip_count++;
	}
}

};

/*This function reads the file line by line and calls further APIs to process data*/
void analyse_file_data(char* file)
{
	IP obj;
	string input;
	ifstream ipRead(file);
	while(ipRead)
	{
		getline(ipRead, input);
		if(input.length())
			obj.validate_ip(input);
	}
	obj.get_total_ip4_count();
    obj.get_total_ip6_count();
    obj.get_unique_ip4_count();
    obj.get_unique_ip6_count();
    obj.get_invalid_ip_count();
}

int main(int argc, char** argv)
{
if(argc > 1)
{
	try{
		analyse_file_data(argv[1]);
	}
	catch(exception e)
	{
		cout<<"Exception captured: "<<e.what()<<endl;
	}
}
else
{
	cout<<"Please provide file name as command line argument"<<endl;
}
return 0;    
}