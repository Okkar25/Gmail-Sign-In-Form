#include <iostream>
#define SIZE 3

using namespace std;

struct db{
	int id;
	int age;
    char name[30];
    char email[50];
    char password[50];
};

struct db info[SIZE];
struct db loaded[SIZE];

/*------- Essential Tools -------*/
int countChar(char toCount[50]);
int findLongest(struct char2dArr data[SIZE]);
bool diyStrCmp(char str1[50],char str2[50]);
void assignArrayToArray(char arr1[50],char *arr2);

/*---------- Display -----------*/
void printArray(char arr[50],int start, int end);
void addChar(char arr[50],char toAdd,int longest);
void drawLine(int sum);
void header(int nameLen,int mailLen,int pwdLen);
void sectorLine(int nameLen,int mailLen,int pwdLen);
void drawEmptyRow(int nameLen,int mailLen,int pwdLen);
void createAndPrintTable(struct db data[SIZE]);
void printData(struct db toPrint[SIZE]);


/*------ Mail Validation -------*/
int isValid(char mail[50]);
int isDuplicate(char email[50]);
void check(char *mail);

/*--- Reading and Writing DB ---*/
void recordToDB();
void loadData();

/*------ main functions ------*/
void registerForm();
void login();
void menu();


int main()
{
	loadData();
	if (loaded[0].name[0] != '\0'){
		printData(loaded);	
	} else{
		menu();
		recordToDB();
		loadData();
		printData(loaded);
	}

	return 0;
}

void menu(){
	int option=1;
	cout << "|======== Menu ========|" << endl;
	cout << "| Press 1 to Register  |" << endl;
	cout << "| Press 2 to Login     |" << endl;
	cout << "+----------------------+" << endl;
	cout << " Enter: ";
	cin >> option;
	cout << "+----------------------+" << endl << endl;
	
	switch (option){
	case 1:
		registerForm();
		printData(info);
		menu();
		return;
	case 2:
		login();
		return;
	default:
		cout << "[x] Invalid input."<<endl;
		cout << "    Please enter 1 to register." << endl;
		cout << "                 2 to login."    << endl;
		menu();
		return;
	}
}

void registerForm(){
	char mail[50];
	cout << "||====== Registeration =====||" << endl;

	for(int i=0; i< SIZE ; i++)
	{	
		cout << "Enter name: ";
		scanf(" %[^\n]",&info[i].name);

		cout << "Enter age: ";
		scanf("%d",&info[i].age);
		while (info[i].age>1000 || info[i].age<=0){
			cout << "[x] Invalid age."<<endl;
			cout << "    Age must be within the range of 1 to 100."<<endl;
			cout << "    Reenter age: ";
			scanf("%d",&info[i].age);
		}

		cout << "Enter email: ";
		scanf(" %[^\n]",&mail);

		check(mail);

		assignArrayToArray(mail,info[i].email);

		cout << "Enter password: ";
		scanf(" %[^\n]",&info[i].password);

		info[i].id = i;
    }
}

void login(){
    char loginEmail[50];
    char loginPwd[50];
    int found  = -1;
    cout << "||========== Login form ==========||" << endl;

    cout << "  Enter your email: ";
    scanf(" %[^\n]",&loginEmail);

    int eFound = isDuplicate(loginEmail);

    if(eFound >= 0){
    	for (int i=0;i<3;i++){ // only 3 attempts are allowed.
    		cout << "  Enter your password: ";
	    	scanf(" %[^\n]",&loginPwd);
	    	if (diyStrCmp(info[eFound].password,loginPwd)){
	    		cout << "<<<< Successful Login >>>>" << endl;
	    		cout << "  Welcome back, " << info[eFound].name << endl;
	    		break;
	    	} else {
	    		cout << "[x] WRONG PASSWORD!" << endl;
	    		cout << "	 Please try again." << endl;
	    	}
    	}
    } else{
        cout << "[x] Invalid email. " << endl;
        cout << "    Please try again. "<< endl;
        login();
    }

}

void check(char *mail)
{
	while (!(isValid(mail)))
	{
		cout << "Enter email: ";
		scanf(" %[^\n]", mail);
	}
	
	int result = isDuplicate(mail);
	while (result>=0)
	{
		cout << "[x] That email already exists." << endl;
		cout << "    Please enter a different email."<< endl << endl;
		cout << "Enter email: ";
		scanf(" %[^\n]",mail);
		
		while (!(isValid(mail)))
		{
			cout << "Enter email: ";
			scanf(" %[^\n]",mail);
		}

		result = isDuplicate(mail);
	}
}

int isValid(char mail[50]){
	int length = countChar(mail);
	int atSymbol = 0;
	bool check = false;

	// The email checkress must start with a letter (no numbers or symbols).
	int a = ("%d",mail[0]);
	bool notCapitalLetter = a < 65 || a > 90;
	bool notSmallLetter   = a < 97 || a > 122;
	if (notCapitalLetter && notSmallLetter){
		cout << "[x] Your Gmail \""<< mail << "\" is invalid !" << endl;
		cout << "[x] The email must start with a letter (no numbers or symbols)."<<endl<<endl;
		return 0;
	}
	if (length < 10) {
		cout << "[x] Your Gmail \"";
		printArray(mail,0,length);
		cout << "\" is invalid !" << endl;
		return 0;
	}

	char domain[10] = {'@', 'g', 'm', 'a', 'i', 'l', '.', 'c', 'o', 'm'};
	int id = 0;
	for(int i=0;i<length;i++)
	{
		char e = mail[i];
		if (e == ' '){
			cout << "[x] Your Gmail \"" << mail << "\" is invalid !" << endl;
			cout << "    There shouldn't be a space in the gmail!" << endl;
			return 0;
		}
		if (e == '@')
		{
			if (length - i != 10)
			{
				cout << endl;
				cout << "[x] Your Gmail \"" << mail << "\" is invalid !" << endl;
				// printArray(mail,0,length);
				// cout << "\" is invalid !" << endl;

				cout << "[x] There must be a 'gmail.com' after '@' NOT '";
				printArray(mail,i+1,length); 
				cout << "'" << endl << endl;
				
				return 0;
			}
			atSymbol = i;
			check = true;
		}
		if (check)
		{
			if (mail[i] != domain[id])
			{
				cout << endl;
				cout << "[x] Your Gmail \"" << mail << "\" is invalid !" << endl;
				
				cout << "[x] There must be a 'gmail.com' after '@' NOT '";
				printArray(mail,atSymbol+1,length); 
				cout << "'" << endl << endl;
				
				return 0;
			}
			id+=1;
		}
	}
	if (!(check)){ // if there was no @
		cout << endl;
		cout << "[x] Your Gmail \"" << mail << "\" is invalid !" << endl;
		cout << "    It's missing @" << endl;
		return 0;
	}

	cout << "[x] Your Gmail \"" << mail << "\" is valid !" << endl << endl;

	return 1;
}

int isDuplicate(char email[50])
{
	bool result = false;
    int secondLen = countChar(email);

    for(int i=0; i<SIZE ; i++)
    {
        int firstLen = countChar(info[i].email);

        if(firstLen == secondLen){
        	result = diyStrCmp(info[i].email,email);
            if (result){
				return i;
			}
        }
    }
    return -1;
}


void assignArrayToArray(char arr1[50],char *arr2){
	for (int i=0;arr1[i]!='\0';i++){
		arr2[i] = arr1[i];
	}
}


// toCount[50] = {'w','i','n','@','g','m','a','i','l','.','c','o','m','\0' , '\0'}
int countChar(char toCount[50])
{
    int charCount = 0;
    for(int gcc=0; gcc<50 ; gcc++)
    {
        if( toCount[gcc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void printArray(char arr[50],int start,int end){
	for (int i=start;i<end;i++){
		cout << arr[i];
	}
}

void addChar(char arr[50],int length,char toAdd,int longest){
	for (int i=0;i<length;i++){
		cout << arr[i];
	}
	for (int i=length;i<=longest;i++){
		cout << toAdd;
	}
}

struct char2dArr {
  char arr[50];	
};

int findLongest(struct char2dArr data[SIZE]){
	int longest=0;
	int len=0;
	for (int i=0;i<3;i++){
		len = countChar(data[i].arr);
		if (len > longest){
			longest = len;
		}
	}
	return longest;
}

void drawLine(int sum){
	cout << "++";
	for (int i=0;i<sum+20;i++){
		cout << "=";
	}
	cout << "++" << endl;
}

void header(int nameLen,int mailLen,int pwdLen){
	char space = ' ';
	cout << "|| ID  | ";
	if (nameLen<=4){
		cout << "Name";
	} else{
		char name[4] = {'N','a','m','e'};
		addChar(name,4,space,nameLen);
	}
	cout << " | Age | ";
	char email[5] = {'E','m','a','i','l'};
	addChar(email,5,space,mailLen);
	cout << "| ";
	char pwdArr[8] = {'P','a','s','s','w','o','r','d'};
	addChar(pwdArr,8,space,pwdLen);
	cout << "||" << endl;
}

void sectorLine(int nameLen,int mailLen,int pwdLen){
	cout <<"||-----|";
	char dash[1] = {'-'};
	char d = '-';
	addChar(dash,1,d,nameLen+1);
	cout << "|-----|";
	addChar(dash,1,d,mailLen+1);            cout << "|";
	addChar(dash,1,d,pwdLen+1);             cout << "||" << endl;
}

void drawEmptyRow(int nameLen,int mailLen,int pwdLen){
	char space[1] = {' '};
	cout << "||     | ";
	addChar(space,1,' ',nameLen);
	cout << "|";       //name
	cout << "     |";  // age
	addChar(space,1,' ',mailLen);          
	cout << " |";//email
	addChar(space,1,' ',pwdLen);           
	cout << " ||" << endl;	
}

void createAndPrintTable(struct db data[SIZE])
{
	// find longest length
	
	// struct char2dArr names[3]    = {*data[0].name,*data[1].name,*data[2].name};
	// struct char2dArr mails[3]   = {*data[0].email,*data[1].email,*data[2].email};
	// struct char2dArr pwds[3]    = {*data[0].password,*data[1].password,*data[2].password};
	// int nameLen = findLongest(names);
	// int mailLen = findLongest(mails);
	// int pwdLen  = findLongest(pwds);

	int nameLen=0;
	int len=0;
	for (int i=0;i<3;i++){
		len = countChar(data[i].name);
		if (len > nameLen){
			nameLen = len;
		}
	}

	int mailLen=0;
	len=0;
	for (int i=0;i<3;i++){
		len = countChar(data[i].email);
		if (len > mailLen){
			mailLen = len;
		}
	}

	int pwdLen =0;
	len=0;
	for (int i=0;i<3;i++){
		len = countChar(data[i].password);
		if (len > pwdLen){
			pwdLen = len;
		}
	}
	
	int sum = nameLen+mailLen+pwdLen;
	drawLine(sum);
	header(nameLen,mailLen,pwdLen);
	sectorLine(nameLen,mailLen,pwdLen);
	
	for (int i=0;i<SIZE;i++)
	{
		                                     
		cout << "||  ";
		cout << data[i].id << "  | "; // id
		addChar(data[i].name,countChar(data[i].name),' ',nameLen);   
		
		cout << "| "; cout << data[i].age;
		if (data[i].age>=100){
			cout << " | ";
		} else{
			cout << "  | ";
		}
		
		addChar(data[i].email,countChar(data[i].email) ,' ',mailLen);  
		cout << "| ";
		
		addChar(data[i].password, countChar(data[i].password),' ',pwdLen);
		cout << "||" << endl; 

		// ||     |    |     |                    |        ||
		drawEmptyRow(nameLen,mailLen,pwdLen);
		
	}
	drawLine(sum);
}


void printData(struct db toPrint[SIZE]){

	createAndPrintTable(toPrint);

    // for(int gcc=0; gcc< SIZE ; gcc++ )
    // {
    // 	cout << endl;
    // 	cout << "   Id       : " << toPrint[gcc].id       << endl;
    //     cout << "   name     : " << toPrint[gcc].name     << endl;
	// 	cout << "   age      : " << toPrint[gcc].age      << endl;
	// 	cout << "   email    : " << toPrint[gcc].email    << endl;
	// 	cout << "   password : " << toPrint[gcc].password << endl << endl;
    // }
}




bool diyStrCmp(char str1[50],char str2[50]){
	for (int i=0;str1[i]!='\0';i++){
		if (str1[i]!=str2[i]){
			return false;
		}
	}
	return true;
}

void recordToDB(){
	FILE *fp = fopen("UserData.txt","w");
    if(fp==NULL){
        cout << "[x] File can't be opened for some reasons." << endl;
        cout << "    Please try again later." << endl;
    } else{
        for (int gcc=0;gcc<SIZE;gcc++){
            fprintf(fp,"%d %d %s %s %s \n", info[gcc].id, info[gcc].age, info[gcc].name, info[gcc].email,info[gcc].password);
        }
        fclose(fp);
        cout << "[+] Recorded the data to UserData.txt" << endl;
    }
}

void loadData(){
	FILE *fp = fopen("UserData.txt","r");
	if(fp==NULL){
        cout << "[x] File can't be opened for some reasons." << endl;
        cout << "    Please try again later." << endl;
    } else{
    	for (int z=0;z<SIZE;z++){
    		fscanf(fp,"%d%d%s%s%s",&loaded[z].id, &loaded[z].age, &loaded[z].name, &loaded[z].email, &loaded[z].password);
    		if (loaded[z].name[0]=='\0'){
    			break;
    		}
    	}
    	fclose(fp);
    }
}
