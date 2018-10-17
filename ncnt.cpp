#include "ncnt.h"

int main(int argc, char** argv)
{
	//Variables
	bool alpha=false;
	bool caseSensitive=false;
	bool bytes=false;
	bool nybbles=false;
	bool hex = false;
	bool verbose = false;
	int numAlpha = 0;
	
	//Parse input
	for(int i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-A") == 0 || strcmp(argv[i], "-a") == 0)
		{
			alpha=true;
		}
		else if(strcmp(argv[i], "-B") == 0 || strcmp(argv[i], "-b") == 0)
		{
			bytes=true;
		}
		else if(strcmp(argv[i], "-N") == 0 || strcmp(argv[i], "-n") == 0)
		{
			nybbles=true;
		}
		else if(strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "-c") == 0)
		{
			caseSensitive=true;
		}
		else if(strcmp(argv[i], "-X") == 0 || strcmp(argv[i], "-x") == 0)
		{
			hex=true;
		}
		else if(strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "-v") == 0)
		{
			verbose=true;
		}
	}
	if(!alpha && !bytes && !nybbles)
	{
		nybbles=true;
	}	
	freopen(NULL, "rb", stdin);
	char buffer[102400]; //char buffer
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), stdin); // Read the file from stdin
    
    for(int i=0; i<bytes_read; i++)
    {
    	if(buffer[i]>64 && buffer[i]<91 || buffer[i]>96 && buffer[i]<122)
    	{
    		numAlpha++; //Number of alphabetic values
    	}
    }
    if(verbose)
    {
    	cout<<"\n**NOTE** 'V' Flag set to ON. Displaying QTY count only for values with at minimum 1 occurrence. 'V' flag only applied to bytes and alpha characters, does not affect nybbles.\n\n";
    }
    if(nybbles)
    {
    	cout<<setw(6)<<"Nybble"<<setw(7)<<"Qty"<<endl;
    	countNybbles(buffer, bytes_read, hex, verbose);
    	cout<<"\n";
    }
    if(bytes)
    {
    	cout<<setw(6)<<"Byte"<<setw(7)<<"Qty"<<endl;
    	countBytes(buffer, bytes_read, hex, verbose);
    	cout<<"\n";
    }
    if(alpha)
    {
    	cout<<setw(6)<<"Alpha"<<setw(7)<<"Qty"<<endl;
    	countAlpha(buffer, bytes_read, numAlpha, caseSensitive, verbose);
    	cout<<"\n";
    }
    else 
    {
    	return -1;
    }
}
void countAlpha(char buffer[], size_t bytes_read, int n, bool caseSensitive, bool verbose)
{
	char lowAlpha[n]; //Store lowercase characters
	char upAlpha[n]; //Store uppercase characters
		
	int k=0;
	int m=0; //Number of elements added to upAlpha
	for(int i=0; i<bytes_read; i++)
	{
		if(caseSensitive && buffer[i] > 64 && buffer[i] < 91) //Uppercase characters 64-91
		{
			upAlpha[m] = buffer[i]; //Add capital letters to new array
			buffer[i] = '.'; //Replace capitals in original with non-alpha value
			m++; //Keeps track of number of elements added to uppercase array
		}
		buffer[i] = tolower(buffer[i]);
		if(buffer[i] > 96 && buffer[i] < 122) //Lowercase characters
		{
			lowAlpha[k] = buffer[i];
			k++;
		}
	}
    k=0; //Holds counted number for each element
    if(caseSensitive)
    {
    	//Count uppercase
    	for(int i=65; i<=90; i++)
    	{
			for(int j=0; j<m; j++)
			{
				if(upAlpha[j]==i)
				{
					k++; //Count number of each character in array
				}
			}
			if(verbose)
			{
				if(k>0)
				{
					cout<<setw(6)<<(char)i<<setw(7)<<k<<endl;
				}
			}
			else
			{
				cout<<setw(6)<<(char)i<<setw(7)<<k<<endl;
			}
			k=0;
		}    	
	}
    //Count lowercase
    for(int i=97; i<=122; i++)
    {
    	for(int j=0; j<n; j++)
    	{
    		if(lowAlpha[j]==i)
    		{
    			k++; //Count number of each character
    		}
    	}
    	if(verbose)
		{
			if(k>0)
			{
				cout<<setw(6)<<(char)i<<setw(7)<<k<<endl;
			}
		}
		else
		{
    		cout<<setw(6)<<(char)i<<setw(7)<<k<<endl;
    	}
    	k=0;
    }    	
}
void countBytes(char buffer[], size_t bytes_read, bool hex, bool verbose)
{
	int k=0;
	for(int i=0; i<256; i++) //Loop through all possible values
	{
		for(int j=0; j<bytes_read; j++)
		{
			if(buffer[j]==i)
			{
				k++; //Increment counter for each occurrence of specified value
			}
		}
		if(hex)
		{
			if(verbose)
			{
				if(k>0)
				{
					cout<<setw(6)<<intToASCIIHex(i)<<setw(7)<<k<<endl;
				}
			}
			else
			{
				cout<<setw(6)<<intToASCIIHex(i)<<setw(7)<<k<<endl;
			}
		}
		else
		{
			if(verbose)
			{
				if(k>0)
				{
					cout<<setw(6)<<i<<setw(7)<<k<<endl;
				}
			}
			else
			{
				cout<<setw(6)<<i<<setw(7)<<k<<endl;
			}
		}
		k=0; //Reset to zero for next iteration
	}
}
void countNybbles(char buffer[], size_t bytes_read, bool hex, bool verbose)
{
	int nybbles[2*bytes_read];
	int k=0; //used as index when adding nybbles to array
	//Separate bytes into nybbles
	for(int i=0; i<bytes_read; i++)
	{
		int temp = buffer[i]; //Sets temp equal to a byte
		int lower = (temp>>0) & 15; //Gets the lower nybble
		int upper = (temp>>4) & 15; //Gets the upper nybble
		nybbles[k] = upper; //Add nybbles to new array
		nybbles[k+1] = lower;
		k=k+2;
	}
	k=0; //Used to count occurrences
	for(int i=0; i<16; i++) //Loop through possible values
	{
		for(int j=0; j<2*bytes_read; j++) //Count occurences of a given value
		{
			if(nybbles[j]==i)
			{
				k++;
			}
		}
		if(hex)
		{
			cout<<setw(6)<<intToASCIIHex(i)<<setw(7)<<k<<endl;
		}
		else
		{
			cout<<setw(6)<<i<<setw(7)<<k<<endl;
		}
		k=0; //Sets count to zero for next iteration
	}
}
string intToASCIIHex(int x)
{
	int remainder;
	string result;
	string stringRemainder;
	char convert[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	if(x==0)
	{
		return "00";
	}
	while(x>0)
	{
		remainder=x%16;
		result = convert[remainder] + result;
		x = x/16;
	}
	if(result.length()==1)
	{
		return '0' + result;
	}
	return result;
}
 

