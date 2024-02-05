#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <windows.h>
#include <direct.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int check(){
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char *path =  _getcwd(NULL, MAX_PATH);
    char sag_path[MAX_PATH];

    while(strlen(path) != 3){
        //printf("1\n");
        sprintf(sag_path, "%s\\sag", path);
        if(GetFileAttributes(sag_path) != INVALID_FILE_ATTRIBUTES){
            //printf("1%s\n", sag_path);
            SetCurrentDirectory(copy_path);
            return 1;
        }
        SetCurrentDirectory("..");
        path = _getcwd(NULL, MAX_PATH);
    }
    
    //SetCurrentDirectory("C:\\sag base");
    SetCurrentDirectory(copy_path);
    return 0;
}

void init(){
    char *copy_path = _getcwd(NULL, MAX_PATH);
    if(check()){
        printf("You've already done this!");
        exit(EXIT_FAILURE);
    }

    mkdir ("sag");
    SetCurrentDirectory("sag");
    FILE* name = fopen("name.txt","w");
    FILE* email = fopen("email.txt","w");
    SetCurrentDirectory("C:\\sag base");
    FILE* globalname = fopen("global name.txt","r");
    FILE* globalemail = fopen("global email.txt","r");
    char a;
    while((a = fgetc(globalname))!= EOF){
        fputc(a,name);
    }
    char b;
    while((b = fgetc(globalemail))!= EOF){
        fputc(b,email);
    }
    fclose(globalemail);
    fclose(globalname);
    fclose(email);
    fclose(name);
    SetCurrentDirectory("C:\\sag base");
    FILE* branch = fopen("branch.txt","w");
    fputs("Master\n",branch);
    fclose(branch);
    SetCurrentDirectory("branches");
    FILE* new = fopen("branches.txt","w");
    fputs("Master\n",new);
    fclose(new);
    SetCurrentDirectory(copy_path);
    SetFileAttributes("sag", FILE_ATTRIBUTE_HIDDEN);
}

void new_name(char* name){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char *path =  _getcwd(NULL, MAX_PATH);
    char sag_path[MAX_PATH];

    while(strlen(path) != 3){
        sprintf(sag_path, "%s\\sag", path);
        if(GetFileAttributes(sag_path) != INVALID_FILE_ATTRIBUTES){
            SetCurrentDirectory(sag_path);
            FILE* file = fopen("name.txt","w");
            fprintf(file,"%s",name);
            fclose(file);
            break;
            }
        SetCurrentDirectory("..");
        path = _getcwd(NULL, MAX_PATH);
    }
    SetCurrentDirectory(copy_path);
}

void new_email(char* email){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char *path =  _getcwd(NULL, MAX_PATH);
    char sag_path[MAX_PATH];

    while(strlen(path) != 3){
        sprintf(sag_path, "%s\\sag", path);
        if(GetFileAttributes(sag_path) != INVALID_FILE_ATTRIBUTES){
            SetCurrentDirectory(sag_path);
            FILE* file = fopen("email.txt","w");
            fprintf(file,"%s",email);
            fclose(file);
            break;
            }
        SetCurrentDirectory("..");
        path = _getcwd(NULL, MAX_PATH);
    }
    SetCurrentDirectory(copy_path);
}

void Globalname(char* name){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *path =  _getcwd(NULL, MAX_PATH);
    SetCurrentDirectory("C:\\sag base");
    FILE* globalname = fopen("global name.txt","w");
    fprintf(globalname,"%s",name);
    fclose(globalname);
    SetCurrentDirectory(path);
    new_name(name);
}

void Globalemail(char* email){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *path =  _getcwd(NULL, MAX_PATH);
    SetCurrentDirectory("C:\\sag base");
    FILE* globalemail = fopen("global email.txt","w");
    fprintf(globalemail,"%s",email);
    fclose(globalemail);
    SetCurrentDirectory(path);
    new_email(email);
}

void add(char* address){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char* path = _getcwd(NULL, MAX_PATH);
    
    //printf("%s\n",copy_path);
    struct stat fileStat;
    stat(address,&fileStat);
    if (S_ISDIR(fileStat.st_mode)) {
        char newname[100];
        for(int i = 0;i<100;i++){
            newname[i] = 0;
        }
        int x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            x = i;
        }
        //x = strlen(address)-x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            newname[x-i] = address[strlen(address)-1-i];
        }
        SetCurrentDirectory("C:\\sag base");
        FILE* list = fopen("staging.txt","a");
        fprintf(list,"%s\n",newname);
        fclose(list);
        DIR* dir;
        struct dirent* entry;
        SetCurrentDirectory(path);
        dir = opendir(address);
        SetCurrentDirectory(address);
        while((entry = readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")!= 0 && strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,"sag")!=0){
                add(entry->d_name);
            }
        }
    } 
    else if (S_ISREG(fileStat.st_mode)) {
        char newname[100];
        for(int i = 0;i<100;i++){
            newname[i] = 0;
        }
        char dirname[200];
        dirname[0] = '\0';
        char address_[MAX_PATH];
        address_[0] = '\0';
        strcat(address_,path);
        char* token = strtok(path,"\\:.");
        while(token != NULL){
            strcat(dirname,token);
            token = strtok(NULL,"\\:.");
        }
        int x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            x = i;
        }
        //x = strlen(address)-x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            newname[x-i] = address[strlen(address)-1-i];
        }
        FILE* source = fopen(address,"r");
        SetCurrentDirectory("C:\\sag base");
        FILE* list = fopen("staging.txt","a");
        fprintf(list,"%s\n",newname);
        fclose(list);
        SetCurrentDirectory("C:\\sag base\\stage");
        struct dirent* entri;
        DIR* directory = opendir("C:\\sag base\\stage");
        int flag = 0;
        while((entri = readdir(directory))!=NULL){
            if(strcmp(entri->d_name,dirname)== 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            mkdir(dirname);
        }
        SetCurrentDirectory(dirname);
        FILE* addd = fopen("address.txt","w");
        fputs(address_,addd);
        FILE* dest = fopen(newname,"w");
        char ch;
        while((ch = fgetc(source))!=EOF){
            fputc(ch,dest);
        }
        fclose(dest);
        fclose(source);
        SetCurrentDirectory(copy_path);
        //printf("%s\n",copy_path);
    }
    else{
        perror("invalid address!");
        exit(EXIT_FAILURE);
    }
    //printf("%s\n",_getcwd(NULL,MAX_PATH));
}

void add_(){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char* copy_path = _getcwd(NULL,MAX_PATH);
    struct dirent* entry;
    DIR* dir = opendir(".");
    printf("files and directories:\n");
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!= 0 && strcmp(entry->d_name,"..")!=0){
            printf("%s\n" , entry->d_name);
        }
    }
    printf("staged:\n");
    SetCurrentDirectory("C:\\sag base");
    FILE* file = fopen("staging.txt","r");
    SetCurrentDirectory(copy_path);
    DIR* directory = opendir(".");
    struct dirent* entri;
    char word[200];
    while((entri = readdir(directory))!=NULL){
        if(strcmp(entri->d_name,".")!= 0 && strcmp(entri->d_name,"..")!=0){
            while(fscanf(file,"%s",word)!=EOF){
                //printf("%s\n",word);
                if(strcmp(word,entri->d_name)==0){
                    printf("%s\n" , entri->d_name);
                }
            }
            rewind(file);
        }
    }
    fclose(file);
    SetCurrentDirectory(copy_path);
}

void delete(const char *dirPath) {
    char* path = _getcwd(NULL,MAX_PATH);
    DIR *dir = opendir(dirPath);
    struct dirent *entry;

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            // It's a regular file, so delete it
            char filePath[MAX_PATH];
            snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);
            remove(filePath);
        } else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // It's a directory (excluding '.' and '..'), so recursively call the function
            char subDirPath[MAX_PATH];
            snprintf(subDirPath, sizeof(subDirPath), "%s/%s", dirPath, entry->d_name);
            delete(subDirPath);
        }
    }

    closedir(dir);
    SetCurrentDirectory(path);
}

int is_directory_empty()
{
    char* path = _getcwd(NULL,MAX_PATH);
    struct dirent *entry;
    DIR *dir = opendir(".");
    int is_empty = 1;
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry -> d_name, ".") && strcmp(entry -> d_name, ".."))
        {
            is_empty = 0;
            break;
        }
    }
    SetCurrentDirectory(path);
    return is_empty;
}

void Empty(char *dirPath) {
    char *copy_path = _getcwd(NULL,MAX_PATH);
    DIR *dir = opendir(dirPath);
    struct dirent *entry;

    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char subDirPath[MAX_PATH];
            sprintf(subDirPath, "%s\\%s", dirPath, entry->d_name);
            DIR *subDir = opendir(subDirPath);
            struct dirent *subEntry = readdir(subDir);
            closedir(subDir);
            SetCurrentDirectory(subDirPath);
            if (is_directory_empty()) {
                SetCurrentDirectory("..");
                char command[MAX_PATH];
                sprintf(command, "rmdir /s /q %s", entry->d_name);
                system(command);
            } else if (subEntry->d_type == DT_DIR) {
                Empty(subDirPath);
            }
        }
    }

    closedir(dir);
    SetCurrentDirectory(copy_path);
}

void reset(char* address){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char* path = _getcwd(NULL, MAX_PATH);
    delete("C:\\sag base\\undo");
    Empty("C:\\sag base\\undo");
    SetCurrentDirectory(copy_path);
    //printf("%s\n",copy_path);
    struct stat fileStat;
    stat(address,&fileStat);
    if (S_ISDIR(fileStat.st_mode)) {
        char newname[100];
        for(int i = 0;i<100;i++){
            newname[i] = 0;
        }
        int x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            x = i;
        }
        //x = strlen(address)-x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            newname[x-i] = address[strlen(address)-1-i];
        }
        SetCurrentDirectory("C:\\sag base");
        FILE *temp;
        temp = fopen("temp.txt", "w");
        FILE* list = fopen("staging.txt","r");
        FILE* second = fopen("reset.txt","a");
        char buffer[100];

        while (fscanf(list, " %99s", buffer) == 1) {
            if (strcmp(buffer, newname) != 0) {
                fprintf(temp, "%s\n", buffer);
            }
            else{
                fprintf(second,"%s\n", buffer);
            }
        }
        fclose(list);
        fclose(temp);
        fclose (second);
        remove("staging.txt");
        rename("temp.txt", "staging.txt");
        DIR* dir;
        struct dirent* entry;
        SetCurrentDirectory(path);
        dir = opendir(address);
        SetCurrentDirectory(address);
        while((entry = readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")!= 0 && strcmp(entry->d_name,"..")!=0){
                reset(entry->d_name);
            }
        }
    } 
    else if (S_ISREG(fileStat.st_mode)) {
        char newname[100];
        for(int i = 0;i<100;i++){
            newname[i] = 0;
        }
        char dirname[200];
        dirname[0] = '\0';
        char* token = strtok(path,"\\:.");
        while(token != NULL){
            strcat(dirname,token);
            token = strtok(NULL,"\\:.");
        }
        int x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            x = i;
        }
        //x = strlen(address)-x;
        for(int i = 0;i<strlen(address);i++){
            if(address[strlen(address)-1-i]=='\\'){
                break;
            }
            newname[x-i] = address[strlen(address)-1-i];
        }
        FILE* source = fopen(address,"r");
        SetCurrentDirectory("C:\\sag base");
        //FILE* list = fopen("staging.txt","a");
        //fprintf(list,"%s\n",newname);
        //fclose(list);
        SetCurrentDirectory("C:\\sag base\\undo");
        struct dirent* entri;
        DIR* directory = opendir("C:\\sag base\\undo");
        int flag = 0;
        while((entri = readdir(directory))!=NULL){
            if(strcmp(entri->d_name,dirname)== 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            mkdir(dirname);
        }
        SetCurrentDirectory(dirname);
        FILE* dest = fopen(newname,"a");
        char buffer1[100];
        while (fscanf(source, "%99s", buffer1) == 1) {
                fprintf(dest,"%s", buffer1);
        }
        fclose(dest);
        fclose(source);
        SetCurrentDirectory("C:\\sag base\\stage");
        SetCurrentDirectory(dirname);
        remove(newname);
        SetCurrentDirectory("C:\\sag base");
        FILE *temp;
        temp = fopen("temp.txt", "w");
        FILE* list = fopen("staging.txt","r");
        FILE* second = fopen("reset.txt","a");
        char buffer[100];

        while (fscanf(list, " %99s", buffer) == 1) {
            if (strcmp(buffer, newname) != 0) {
                fprintf(temp, "%s\n", buffer);
            }
            else{
                fprintf(second,"%s\n", buffer);
            }
        }
        fclose(list);
        fclose(temp);
        fclose (second);
        remove("staging.txt");
        rename("temp.txt", "staging.txt");
        SetCurrentDirectory(copy_path);
        //printf("%s\n",copy_path);
    }
    Empty("C:\\sag base\\stage");
    SetCurrentDirectory(copy_path);
}

void undo_end(){
    char* copy_path = _getcwd(NULL,MAX_PATH);
    struct dirent* entry;
    DIR* dir = opendir("C:\\sag base\\stage");
    while((entry = readdir(dir))!=NULL){
        if(entry -> d_type != DT_DIR){
            SetCurrentDirectory("C:\\sag base\\stage");
            remove(entry->d_name);
        }
    }
    SetCurrentDirectory("C:\\sag base");
    FILE* source = fopen("reset.txt","r");
    FILE* dest = fopen("staging.txt","a");
    char buffer[100];
    while (fscanf(source, " %99s", buffer) == 1) {
        fprintf(dest,"%s\n", buffer);
    }
    fclose(source);
    fclose(dest);
    remove("reset.txt");
    SetCurrentDirectory(copy_path);
}

void undo() {
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char *copy_path = _getcwd(NULL, MAX_PATH);
    char* path = _getcwd(NULL, MAX_PATH);
    DIR* dir = opendir("C:\\sag base\\undo");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        SetCurrentDirectory("C:\\sag base\\stage");
        char command[MAX_PATH];
        sprintf(command,"xcopy ..\\undo\\%s /E", entry->d_name);
        SetCurrentDirectory("C:\\sag base\\stage");
        system(command);

    }
    undo_end();
    SetCurrentDirectory(copy_path);
}

int number(){
    char* path = _getcwd(NULL,MAX_PATH);
    SetCurrentDirectory("C:\\sag base\\stage");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
            DIR* new = opendir(entry->d_name);
            struct dirent* entery;
            while((entery = readdir(new))!= NULL){
                if(strcmp(entery->d_name,".") != 0 && strcmp(entery->d_name,"..")!= 0){
                    num++;
                }
            }
        }
    }
    SetCurrentDirectory(path);
    return num;
}

void commit(char* info){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    if(strlen(info)>72){
        perror("message is too long!\n");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\possible");
    FILE* possible = fopen("possible.txt","r");
    char poss[10];
    poss[0] = '\0';
    fgets(poss,sizeof(poss),possible);
    if(strcmp(poss,"0")==0){
        perror("Please checkout to HEAD!\n");
        exit(EXIT_FAILURE);
    }
    int tedad = number();
    SetCurrentDirectory(path);
    SetCurrentDirectory("sag");
    printf("%s\n",_getcwd(NULL,MAX_PATH));
    char username[MAX_PATH];
    //username[0] = '\0';
    FILE* esm = fopen("name.txt","r");
    fgets(username,MAX_PATH,esm);
    fclose(esm);
    char branch[MAX_PATH];
    branch[0] = '\0';
    SetCurrentDirectory("C:\\sag base");
    FILE* x = fopen("branch.txt","r");
    fgets(branch,MAX_PATH,x);
    fclose(x);
    SetCurrentDirectory("C:\\sag base");
    DIR* dir = opendir("C:\\sag base\\commit");
    struct dirent* entry;
    int index = 0;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!= 0 && strcmp(entry->d_name,"..")!=0){
            index++;
        }
    }
    index = index/2;
    SetCurrentDirectory("commit");
    char name[100];
    char infoname[100];
    sprintf(name,"%d",index);
    sprintf(infoname,"%d.txt",index);
    FILE* file = fopen(infoname,"w");
    time_t currentTime;
    struct tm* localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    fprintf(file,"date: %d-%02d-%02d %02d:%02d\nmessage: %s\nname: %s\nid: %s\nbranch: %s\nnumber of files: %d\n\n",localTime->tm_year+1900,localTime->tm_mon + 1,localTime->tm_mday,localTime->tm_hour,localTime->tm_min , info,username,name,branch,tedad);
    
    mkdir(name);
    SetCurrentDirectory(name);
    char command[MAX_PATH];
    sprintf(command,"xcopy ..\\..\\stage /E");
    system(command);
    delete("C:\\sag base\\stage");
    Empty("C:\\sag base\\stage");
    fclose(file);
    SetCurrentDirectory("C:\\sag base");
    remove("staging.txt");
    FILE* filee = fopen("staging.txt","w");
    fclose(filee);
    SetCurrentDirectory(path);

}

void log(){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        FILE* file = fopen(name,"r");
        char buffer[MAX_PATH];
        char c;
        int index = 0;
        while((c = fgetc(file))!= EOF){
            buffer[index] = c;
            index ++;
        }
        buffer[index] = '\0';
        printf("%s",buffer);
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void log_branch(char* string){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    char word[MAX_PATH];
    word[0] = '\0';
    sprintf(word,"branch: %s",string);
    //printf("%s\n",word);
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        FILE* file = fopen(name,"r");
        char buffer[MAX_PATH];
        char c;
        int index = 0;
        while((c = fgetc(file))!= EOF){
            buffer[index] = c;
            index ++;
        }
        buffer[index] = '\0';
        char line[1000];
        int flag = 0;
        fseek(file,0,SEEK_SET);
        while(fgets(line,sizeof(line),file)){
            //printf("%s\n",line);
            if(strstr(line , word) != NULL){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            printf("%s",buffer);
        }
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
    
}

void log_author(char* string){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    char word[MAX_PATH];
    sprintf(word,"name: %s",string);
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        FILE* file = fopen(name,"r");
        char buffer[MAX_PATH];
        char c;
        int index = 0;
        while((c = fgetc(file))!= EOF){
            buffer[index] = c;
            index ++;
        }
        buffer[index] = '\0';
        char line[1000];
        int flag = 0;
        fseek(file,0,SEEK_SET);
        while(fgets(line,sizeof(line),file)){
            if(strstr(line , word) != NULL){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            printf("%s",buffer);
        }
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void log_search(char* string){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        FILE* file = fopen(name,"r");
        char buffer[MAX_PATH];
        char c;
        int index = 0;
        while((c = fgetc(file))!= EOF){
            buffer[index] = c;
            index ++;
        }
        buffer[index] = '\0';
        char line[1000];
        int flag = 0;
        int message = 0;
        int namee = 0;
        fseek(file,0,SEEK_SET);
        while(fgets(line,sizeof(line),file)){
            if(strstr(line , "message: ") != NULL){
                message = 1;
            }
            if(strstr(line , "name: ") != NULL){
                namee = 1;
            }
            if(strstr(line , string) != NULL){
                flag = 1;
                break;
            }
        }
        if(flag == 1 && message == 1 && namee == 0){
            printf("%s",buffer);
        }
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void log_n(int n){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    for(int i = num-1 ; i>= num-n ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        FILE* file = fopen(name,"r");
        char buffer[MAX_PATH];
        char c;
        int index = 0;
        while((c = fgetc(file))!= EOF){
            buffer[index] = c;
            index ++;
        }
        buffer[index] = '\0';
        printf("%s",buffer);
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void log_date(char* date){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        char line1[100];
        FILE* file = fopen(name,"r");
        fgets(line1,sizeof(line1),file);
        int flag = 0;
        for(int i = 0; i<16 ; i++){
            //printf("%c,%c\n",date[i],line1[i+6]);
            if(date[i] > line1[i+6]){
                flag = 1;
                break;
                //printf("%c");
            }
        }
        if(flag == 0){
            fseek(file,0,SEEK_SET);
            char c;
            while((c=fgetc(file))!=EOF){
                putchar(c);
           } 
        }
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void log_date_(char* date){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    SetCurrentDirectory("C:\\sag base\\commit");
    int num = 0;
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!= NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!= 0){
           num++;
        }
    }
    num = num/2;
    for(int i = num-1 ; i>= 0 ; i--){
        char name[MAX_PATH];
        sprintf(name,"%d.txt",i);
        char line1[100];
        FILE* file = fopen(name,"r");
        fgets(line1,sizeof(line1),file);
        int flag = 0;
        for(int i = 0; i<16 ; i++){
            //printf("%c,%c\n",date[i],line1[i+6]);
            if(date[i] < line1[i+6]){
                flag = 1;
                break;
                //printf("%c");
            }
        }
        if(flag == 0){
            fseek(file,0,SEEK_SET);
            char c;
            while((c=fgetc(file))!=EOF){
                putchar(c);
           } 
        }
        fclose(file);
    }
    closedir(dir);
    SetCurrentDirectory(path);
}

void status(){
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char* path = _getcwd(NULL,MAX_PATH);
    char dirname[200];
        dirname[0] = '\0';
        char* token = strtok(path,"\\:.");
        while(token != NULL){
            strcat(dirname,token);
            token = strtok(NULL,"\\:.");
        }
    DIR* commit = opendir("C:\\sag base\\commit");
    DIR* dir = opendir(".");
    struct dirent* entry;
    FILE* file = fopen("C:\\sag base\\staging.txt","r");
    char x;
    char y = ' ';
    struct dirent* entri;
    DIR* directory = opendir("C:\\sag base\\commit");
    struct dirent* hello;
    struct dirent* search;
    int index = 0;
    while((hello = readdir(directory))!=NULL){
        if(strcmp(hello->d_name,".")!= 0 && strcmp(hello->d_name,"..")!=0){
            index++;
        }
    }
    index = index/2;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name,"..")!= 0 && strcmp(entry->d_name,"sag" )!= 0 && entry->d_type == DT_REG){
            FILE* file1 = fopen(entry->d_name,"r");
            x = '-';
            char line[100];
            line[0] = '\0';
            fseek(file,0,SEEK_SET);
            while(fgets(line,sizeof(line),file)){
                line[strlen(line)-1] = '\0';
                //printf("%s\n",line);
                if(strcmp(entry->d_name,line)==0){
                    x = '+';
                    break;
                }
            }
            char name[100];
            name[0] = '\0';
            int flag = 0;
            for(int i = index-1;i>=0;i--){
                sprintf(name,"%d",i);
                SetCurrentDirectory("C:\\sag base\\commit");
                SetCurrentDirectory(name);
                DIR* z = opendir(".");
                while((entri = readdir(z))!=NULL){
                    //char* address = _getcwd(NULL,MAX_PATH);
                    //printf("%s %s\n",entri->d_name,dirname);
                    //printf("1\n");
                    if(strcmp(entri->d_name,dirname)==0){
                        SetCurrentDirectory(dirname);
                        DIR* place = opendir(".");
                        while((search = readdir(place))!= NULL){
                            if(strcmp(search->d_name,entry->d_name)==0){
                                flag = 1;
                                FILE* file2 = fopen(search->d_name,"r");
                                char buffer1[1000];
                                char buffer2[1000];
                                while(fgets(buffer1,sizeof(buffer1),file1)){
                                    fgets(buffer2,sizeof(buffer2),file2);
                                    if(strcmp(buffer1,buffer2)!=0){
                                        y = 'M';
                                        break;
                                    }
                                }
                                break;
                            }
                            if(flag == 1){
                                break;
                            }
                        }
                    }
                    if(flag == 1){
                        break;
                    }
                }
                if(flag == 1){
                    break;
                }
            }
            if (flag == 0){
                printf("%s %cA\n",entry->d_name,x);
            }
            else{
                printf("%s %c%c\n",entry->d_name,x,y);
            }
            
        } 
    }
    DIR* dirr = opendir("C:\\sag base\\commit");
    struct dirent* entryy;
    int indexx = 0;
    while((entryy = readdir(dirr))!=NULL){
        if(strcmp(entryy->d_name,".")!= 0 && strcmp(entryy->d_name,"..")!=0){
            indexx++;
        }
    }
    indexx = indexx/2;
    DIR* new_dir;
    struct dirent* a;
    for(int i = indexx-1 ; i>=0 ;i--){
        SetCurrentDirectory("C:\\sag base\\commit");
        char esm[5];
        sprintf(esm,"%d",i);
        SetCurrentDirectory(esm);
        //  char* d = _getcwd(NULL,MAX_PATH);
        //  printf("%s\n",esm);
        new_dir = opendir(".");
        while((a = readdir(new_dir))!=NULL){
            if(strcmp(a->d_name,".")!= 0 && strcmp(a->d_name,"..")!=0){
                SetCurrentDirectory(a->d_name);
                DIR* new = opendir(".");
                FILE* address = fopen("address.txt","r");
                char add[MAX_PATH];
                fgets(add,sizeof(add),address);
                struct dirent* b;
                char* masir = _getcwd(NULL,MAX_PATH);
                while((b=readdir(new))!=NULL){
                    if(strcmp(b->d_name,".")!= 0 && strcmp(b->d_name,"..")!=0 && strcmp(b->d_name,"address.txt")!=0){
                        int flag = 0;
                        SetCurrentDirectory(add);
                        struct dirent* c;
                        DIR* dir2 = opendir(".");
                        while((c=readdir(dir2))!=NULL){
                            if(strcmp(b->d_name,c->d_name)==0){
                                flag = 1;
                                break;
                            }
                        }
                        SetCurrentDirectory(masir);
                        if(flag ==0){
                            printf("%s %cD",b->d_name,x);
                    }
                    }
                }
            }
        }
    }
    SetCurrentDirectory(path);
    
}

void branch(char* name){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen("branches.txt","r");
    char line[100];
    while(fgets(line,sizeof(line),file)){
        if(strcmp(name,line)==0){
            fseek(file,0,SEEK_SET);
            fclose(file);
            perror("Branch currently exists!\n");
            exit(EXIT_FAILURE);
        }
    }
    SetCurrentDirectory("C:\\sag base\\branches");
    FILE* filee = fopen("branches.txt","a");
    fprintf(filee,"%s\n",name);
    fseek(file,0,SEEK_SET);
    fclose(file);
    // strcat(name,"\n");
    //SetCurrentDirectory("C:\\sag base");
    //printf("%s\n",_getcwd(NULL,MAX_PATH));
    SetCurrentDirectory("C:\\sag base");
    FILE* branch_ = fopen("branch.txt","w");
    fputs(name,branch_);
    //fclose(filee);
    //fclose(branch_);
    DIR* dirr = opendir("C:\\sag base\\commit");
    struct dirent* entryy;
    int indexx = 0;
    while((entryy = readdir(dirr))!=NULL){
        if(strcmp(entryy->d_name,".")!= 0 && strcmp(entryy->d_name,"..")!=0){
            indexx++;
        }
    }
    indexx = indexx/2-1;
    char esm[100];
    sprintf(esm,"%d",indexx);
    SetCurrentDirectory(esm);
    DIR* dir = opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            SetCurrentDirectory(entry->d_name);
            char address[100];
            FILE* add = fopen("address.txt","r");
            fgets(address,sizeof(address),add);
            struct dirent* entri;
            DIR* directory = opendir(".");
            while((entri = readdir(directory))!=NULL){
                if(strcmp(entri->d_name,".")!=0 && strcmp(entri->d_name,"..")!=0&&strcmp(entri->d_name,"address.txt")!=0){
                    char* copy = _getcwd(NULL,MAX_PATH);
                    FILE* source = fopen(entri->d_name,"r");
                    SetCurrentDirectory(address);
                    FILE* dest = fopen(entri->d_name,"w");
                    char line[100];
                    while(fgets(line,sizeof(line),source)){
                        fputs(line,dest);
                    }
                    fclose(source);
                    fclose(dest);
                    SetCurrentDirectory(copy);
                }
            }
            SetCurrentDirectory("..");
        }
    }
    SetCurrentDirectory(path);
}

void branch_(){
    char* path = _getcwd(NULL,MAX_PATH);
    SetCurrentDirectory("C:\\sag base\\branches");
    FILE* file = fopen("branches.txt","r");
    char line[100];
    while(fgets(line,sizeof(line),file)){
        puts(line);
    }
    SetCurrentDirectory(path);
}

void checkout(char* namee){
    char* path = _getcwd(NULL,MAX_PATH);
    if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
    char dirname[200];
        dirname[0] = '\0';
        char* token = strtok(path,"\\:.");
        while(token != NULL){
            strcat(dirname,token);
            token = strtok(NULL,"\\:.");
        }
    DIR* commit = opendir("C:\\sag base\\commit");
    DIR* dir = opendir(".");
    struct dirent* entry;
    FILE* file = fopen("C:\\sag base\\staging.txt","r");
    int x;
    struct dirent* entri;
    DIR* directory = opendir("C:\\sag base\\commit");
    struct dirent* hello;
    struct dirent* search;
    int index = 0;
    while((hello = readdir(directory))!=NULL){
        if(strcmp(hello->d_name,".")!= 0 && strcmp(hello->d_name,"..")!=0){
            index++;
        }
    }
    index = index/2;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name , ".") != 0 && strcmp(entry->d_name,"..")!= 0 && strcmp(entry->d_name,"sag" )!= 0 && entry->d_type == DT_REG){
            x = 0;
            FILE* file1 = fopen(entry->d_name,"r");
            char name[100];
            name[0] = '\0';
            int flag = 0;
            for(int i = index-1;i>=0;i--){
                sprintf(name,"%d",i);
                SetCurrentDirectory("C:\\sag base\\commit");
                SetCurrentDirectory(name);
                DIR* z = opendir(".");
                while((entri = readdir(z))!=NULL){
                    //char* address = _getcwd(NULL,MAX_PATH);
                    //printf("%s %s\n",entri->d_name,dirname);
                    //printf("1\n");
                    if(strcmp(entri->d_name,dirname)==0){
                        SetCurrentDirectory(dirname);
                        DIR* place = opendir(".");
                        while((search = readdir(place))!= NULL){
                            if(strcmp(search->d_name,entry->d_name)==0){
                                x = 1;
                                flag = 1;
                                FILE* file2 = fopen(search->d_name,"r");
                                char buffer1[1000];
                                char buffer2[1000];
                                while(fgets(buffer1,sizeof(buffer1),file1)){
                                    fgets(buffer2,sizeof(buffer2),file2);
                                    if(strcmp(buffer1,buffer2)!=0){
                                        x = 0;
                                        break;
                                    }
                                }
                                break;
                            }
                            if(flag == 1){
                                break;
                            }
                        }
                    }
                    if(flag == 1){
                        break;
                    }
                }
                if(flag == 1){
                    break;
                }
            }
        } 
    }
    if(x == 0){
        perror("Please first commit changes!\n");
        exit(EXIT_FAILURE);
    }
    int number = 1;
    for(int i = 0;i<strlen(namee);i++){
        if(namee[i] > 57 || namee[i] < 48){
            number = 0;
            break;
        }
    }
    if(strcmp(namee,"HEAD") == 0){
        SetCurrentDirectory("C:\\sag base\\possible");
        FILE* possible = fopen("possible.txt","w");
        fputs("1",possible);
        SetCurrentDirectory("C:\\sag base\\commit");
        char nam[100];
        nam[0] = '\0';
        sprintf(nam,"%d",index-1);
        DIR* v = opendir(nam);
        struct dirent* n;
        SetCurrentDirectory(nam);
        while((n=readdir(v))!=NULL){
            if(strcmp(n->d_name,".")!=0 && strcmp(n->d_name,"..")!=0){
                SetCurrentDirectory(n->d_name);
                FILE* address = fopen("address.txt","r");
                char path_[MAX_PATH];
                path_[0] = '\0';
                fgets(path_,sizeof(path_),address);
                DIR* last = opendir(".");
                struct dirent* files;
                char* copy = _getcwd(NULL,MAX_PATH);
                while((files = readdir(last))!=NULL){
                    if(strcmp(files->d_name,".")!=0 && strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,"address.txt") != 0){
                        FILE* source = fopen(files->d_name,"r");
                        SetCurrentDirectory(path_);
                        char line[100];
                        FILE* dest = fopen(files->d_name,"w");
                        while(fgets(line,sizeof(line),source)){
                            fputs(line,dest);
                        }
                        SetCurrentDirectory(copy);

                    }
                }
            }
        }
    }
    else if(number == 1){
        int num = 0;
        for(int i = 0;i<strlen(namee);i++){
            num = num*10+namee[i]-48;
        }
        printf("%d %d\n",num,index);
        if(num>=index || num < 0){
            perror("invalid id!\n");
            exit(EXIT_FAILURE);
        }
        SetCurrentDirectory("C:\\sag base\\possible");
        FILE* possible = fopen("possible.txt","w");
        if(num == index-1){
            fputs("1",possible);
        }
        else{
            fputs("0",possible);
        }
        SetCurrentDirectory("C:\\sag base\\commit");
        char nam[100];
        nam[0] = '\0';
        sprintf(nam,"%d",num);
        DIR* v = opendir(nam);
        struct dirent* n;
        SetCurrentDirectory(nam);
        while((n=readdir(v))!=NULL){
            if(strcmp(n->d_name,".")!=0 && strcmp(n->d_name,"..")!=0){
                SetCurrentDirectory(n->d_name);
                FILE* address = fopen("address.txt","r");
                char path_[MAX_PATH];
                path_[0] = '\0';
                fgets(path_,sizeof(path_),address);
                DIR* last = opendir(".");
                struct dirent* files;
                char* copy = _getcwd(NULL,MAX_PATH);
                while((files = readdir(last))!=NULL){
                    if(strcmp(files->d_name,".")!=0 && strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,"address.txt") != 0){
                        FILE* source = fopen(files->d_name,"r");
                        SetCurrentDirectory(path_);
                        char line[100];
                        FILE* dest = fopen(files->d_name,"w");
                        while(fgets(line,sizeof(line),source)){
                            fputs(line,dest);
                        }
                        SetCurrentDirectory(copy);

                    }
                }
            }
        }
    }
    else{
        SetCurrentDirectory("C:\\sag base\\commit");
        char word[100];
        word[0] = '\0';
        sprintf(word,"branch: %s",namee);
        printf("%s\n", word);
        char x[100];
        int flag = 0;
        int folder;
        for(int i = index-1;i>=0;i--){
            sprintf(x,"%d.txt",i);
            FILE* id = fopen(x,"r");
            char khat[100];
            khat[0] = '\0';
            while(fgets(khat,sizeof(khat),id)){
                printf("%s\n",khat);
                if(strcmp(khat,word) == 0){
                    flag = 1;
                    folder = i;
                    break;
                }
            }
            if(flag == 1){
                break;
            }
        }
        if(flag == 0){
            perror("invalid branch name!\n");
            exit(EXIT_FAILURE);
        }
        SetCurrentDirectory("C:\\sag base\\possible");
        FILE* possible = fopen("possible.txt","w");
        if(folder == index-1){
            fputs("1",possible);
        }
        else{
            fputs("0",possible);
        }
        SetCurrentDirectory("C:\\sag base\\commit");
        char nam[100];
        nam[0] = '\0';
        sprintf(nam,"%d",folder);
        DIR* v = opendir(nam);
        struct dirent* n;
        SetCurrentDirectory(nam);
        while((n=readdir(v))!=NULL){
            if(strcmp(n->d_name,".")!=0 && strcmp(n->d_name,"..")!=0){
                SetCurrentDirectory(n->d_name);
                FILE* address = fopen("address.txt","r");
                char path_[MAX_PATH];
                path_[0] = '\0';
                fgets(path_,sizeof(path_),address);
                DIR* last = opendir(".");
                struct dirent* files;
                char* copy = _getcwd(NULL,MAX_PATH);
                while((files = readdir(last))!=NULL){
                    if(strcmp(files->d_name,".")!=0 && strcmp(files->d_name,"..")!=0 && strcmp(files->d_name,"address.txt") != 0){
                        FILE* source = fopen(files->d_name,"r");
                        SetCurrentDirectory(path_);
                        char line[100];
                        FILE* dest = fopen(files->d_name,"w");
                        while(fgets(line,sizeof(line),source)){
                            fputs(line,dest);
                        }
                        SetCurrentDirectory(copy);

                    }
                }
            }
        }
    }
    SetCurrentDirectory(path);
}

int main(int argc , char** argv){
    if (argc < 2){
        perror("invalid command\n");
        return 1;
    }
    if(strcmp(argv[1],"init")==0){
        if(argc != 2){
            perror("invalid command\n");
            return 1;
        }
        else{
            init();
            return 0;
        }    
    }
    if (strcmp(argv[1] , "config") == 0){
        if(strcmp(argv[2],"-global") == 0){
            if(strcmp(argv[3],"user.name") == 0){
                Globalname(argv[4]);
            }
            else if(strcmp(argv[3],"user.email") == 0){
                Globalemail(argv[4]);
            }
            else{
            perror("invalid command\n");
            return 1;
            }
        }
        else if(strcmp(argv[2],"user.name")==0){
            new_name(argv[3]);
        }
        else if(strcmp(argv[2],"user.email")==0){
            new_email(argv[3]);
        }
        else{
             perror("invalid command\n");
            return 1;
        }
    }
    if(strcmp(argv[1],"add")==0){
        if(argc == 3 && strcmp(argv[2],"-n")!= 0 && strcmp(argv[2],"-f")!= 0){
            int flag = 0;
            for(int i = 0;i<strlen(argv[2]);i++){
                if(argv[2][i] == '*'){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                add(argv[2]);
            }
            else{
                for(int i = 2;i<argc;i++){
                    add(argv[i]);
                }
            }
        }
        else if(strcmp(argv[2] ,"-f")==0){
            for(int i = 3;i<argc;i++){
                add(argv[i]);
            }
        }
        else if(strcmp(argv[2],"-n")==0){
            //printf("1\n");
            add_();
        }
    }
    if(strcmp(argv[1],"reset")==0){
        if(strcmp(argv[2],"-undo") == 0){
            undo();
        }
        else{
            reset(argv[2]);
        }
    }
    if(strcmp(argv[1],"commit")==0 && strcmp(argv[2],"-m")==0 && argc>3){
        if(argc>4){
            if(argv[3][0] != '\"' || argv[argc-1][strlen(argv[argc-1])-1] != '\"'){
                perror("invalid command!\n");
                exit(EXIT_FAILURE);
            }
            else{
                char new[MAX_PATH];
                new[0] = '\0';
                for(int i = 3;i<argc;i++){
                    strcat(new,argv[i]);
                    strcat(new," ");
                }
                commit(new);
            }
        }
        else{
            commit(argv[3]);
        }
    }
    if(strcmp(argv[1],"commit")==0 && strcmp(argv[2],"-s")==0 && argc>3){
        char* path = _getcwd(NULL,MAX_PATH);
        int length = argc-3;
        char new[100];
        new[0] = '\0';
        int flag = 0;
        for(int i = 3;i<argc;i++){
            strcat(new,argv[i]);
            if(i!=argc-1){
                strcat(new," ");
            }
            else{
                strcat(new,"\0");
            }
        }
        //printf("%s",new);
        strcat(new,".txt");
        SetCurrentDirectory("C:\\sag base\\shortcuts");
        DIR* dir = opendir(".");
        struct dirent* entry;
        while((entry = readdir(dir))!=NULL){
            //printf("%s\n",entry->d_name);
            if(strcmp(entry->d_name,new)==0){
                flag = 1;
                char message[100];
                FILE* file = fopen(new,"r");
                fgets(message,sizeof(message),file);
                SetCurrentDirectory(path);
                commit(message);
                fclose(file);
                break;
            }
        }
        SetCurrentDirectory(path);
        if(flag == 0){
            perror("shortcut doesn't exist!\n");
            exit(EXIT_FAILURE);
        }
        
    }
    if(strcmp(argv[1],"set")==0 && strcmp(argv[2],"-m")==0 && argc>3){
        if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
        int index = 3;
        while(strcmp(argv[index],"-s")!=0){
            index++;
        }
        int length1 = index-3;
        int length2 = argc - index-1;
        char name[100];
        name[0] = '\0';
        char shortcut[100];
        shortcut[0] = '\0';
        for(int i = 5;i<5+length2;i++){
            strcat(name,argv[i]);
            if(i!=4+length1){
                strcat(name," ");
            }
            else{
                strcat(name,"\0");
            }
        }
        for(int i = 3;i<3+length1;i++){
            strcat(shortcut,argv[i]);
            if(i!=2+length1){
                strcat(shortcut," ");
            }
            else{
                strcat(shortcut,"\0");
            }
        }
        strcat(name,".txt");
        char* path = _getcwd(NULL,MAX_PATH);
        SetCurrentDirectory("C:\\sag base\\shortcuts");
        DIR* dir = opendir(".");
        struct dirent* entry;
        int flag = 0;
        while((entry = readdir(dir))!=NULL){
            if(strcmp(name, entry->d_name) == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 1){
            perror("shortcut exists!\n");
            exit(EXIT_FAILURE);
        }
        else{
            FILE* file = fopen(name,"w");
            fputs(shortcut,file);
            fclose(file);
        }
        SetCurrentDirectory(path);
        
    }
    if(strcmp(argv[1],"replace")==0 && strcmp(argv[2],"-m")==0 && argc>3){
        if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
        int index = 3;
        while(strcmp(argv[index],"-s")!=0){
            index++;
        }
        int length1 = index-3;
        int length2 = argc - index-1;
        char name[100];
        name[0] = '\0';
        char shortcut[100];
        shortcut[0] = '\0';
        for(int i = 5;i<5+length2;i++){
            strcat(name,argv[i]);
            if(i!=4+length1){
                strcat(name," ");
            }
            else{
                strcat(name,"\0");
            }
        }
        for(int i = 3;i<3+length1;i++){
            strcat(shortcut,argv[i]);
            if(i!=2+length1){
                strcat(shortcut," ");
            }
            else{
                strcat(shortcut,"\0");
            }
        }
        strcat(name,".txt");
        char* path = _getcwd(NULL,MAX_PATH);
        SetCurrentDirectory("C:\\sag base\\shortcuts");
        DIR* dir = opendir(".");
        struct dirent* entry;
        int flag = 0;
        while((entry = readdir(dir))!=NULL){
            if(strcmp(name, entry->d_name) == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            perror("shortcut doesn't exist!\n");
            exit(EXIT_FAILURE);
        }
        else{
            FILE* file = fopen(name,"w");
            fputs(shortcut,file);
            fclose(file);
        }
        SetCurrentDirectory(path);
    }
    if(strcmp(argv[1],"remove")==0 && strcmp(argv[2],"-s")==0 && argc>3){
        if(check() == 0){
        perror("repo doesn't exist!");
        exit(EXIT_FAILURE);
    }
        int length = argc-3;
        char name[100];
        name[0] = '\0';
        for(int i = 3;i<3+length;i++){
            strcat(name,argv[i]);
            if(i!=2+length){
                strcat(name," ");
            }
            else{
                strcat(name,"\0");
            }
        }
        strcat(name,".txt");
        char* path = _getcwd(NULL,MAX_PATH);
        SetCurrentDirectory("C:\\sag base\\shortcuts");
        DIR* dir = opendir(".");
        struct dirent* entry;
        int flag = 0;
        while((entry = readdir(dir))!=NULL){
            if(strcmp(name, entry->d_name) == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            perror("shortcut doesn't exist!\n");
            exit(EXIT_FAILURE);
        }
        else{
            remove(name);
            
        }
        SetCurrentDirectory(path);
    }
    if(strcmp(argv[1],"log") == 0){
        if(argc == 2){
            log();
        }
        else if(argc == 4 && strcmp(argv[2],"-n") == 0){
            int n = 0;
            for(int i = 0;i<strlen(argv[3]);i++){
                n = n*10 + argv[3][i] - 48;
            }
            log_n(n);
        }
        else if(argc == 4 &&strcmp(argv[2] , "-branch") == 0){
            argv[3][strlen(argv[3])] = '\0';
            log_branch(argv[3]);
            //printf("1\n");
        }
        else if(argc == 4 &&strcmp(argv[2] , "-author") == 0){
            argv[3][strlen(argv[3])] = '\0';
            log_author(argv[3]);
        }
        else if(argc == 4 &&strcmp(argv[2] , "-search") == 0){
            argv[3][strlen(argv[3])] = '\0';
            log_search(argv[3]);
        }
        else if(argc == 5 &&strcmp(argv[2] , "-since") == 0){
            //printf("1\n");
            argv[3][strlen(argv[3])] = '\0';
            argv[4][strlen(argv[4])] = '\0';
            strcat(argv[3]," ");
            strcat(argv[3] , argv[4]);
            //printf("%s\n",argv[3]);
            log_date(argv[3]);
        }
        else if(argc == 5 &&strcmp(argv[2] , "-before") == 0){
            //printf("1\n");
            argv[3][strlen(argv[3])] = '\0';
            argv[4][strlen(argv[4])] = '\0';
            strcat(argv[3]," ");
            strcat(argv[3] , argv[4]);
            //printf("%s\n",argv[3]);
            log_date_(argv[3]);
        }
        
    }
    if(strcmp(argv[1], "status") ==0 && argc == 2){
        status();
    }
    if(strcmp(argv[1],"branch") == 0 && (argc == 3 || argc == 2)){
        if(argc == 3){
            branch(argv[2]);
        }
        else{
            branch_();
        }
    }
    if(strcmp(argv[1],"checkout")==0 && argc == 3){
        checkout(argv[2]);
    }

}