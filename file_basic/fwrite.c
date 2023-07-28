#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//test에 사용할 struct
struct person
{
    char name[20];
    int age;
};

static int write_to_file(void)
{
    FILE *fp= NULL;

    struct person lim = {
        .name = "LIM",
        .age = 20
    };

    struct person kim = {
        .name = "KIM",
        .age = 20
    };

    if(!(fp = fopen("persons", "w"))){
        return -1;
    }
    
    if(fwrite(&lim, sizeof(struct person), 1, fp) != 1){
        goto err;
    }
    if(fwrite(&kim, sizeof(struct person), 1, fp) != 1){
        goto err;
    }


    fclose(fp);
    return 0;

err: 
    if (fp) {
        fclose(fp);
    }
    return -1;

}

static int read_from_file(void)
{
    FILE *fp;
    struct person persons[2];

    if(!(fp = fopen("persons", "r"))){
        return -1;
    }

    if(fread(persons, sizeof(struct person), 2, fp) != 2){
        fclose(fp);
        return -1;
    }

    fclose(fp);

    for(int i = 0; i<2; i++){
        printf("name : %s, age : %d\n",
                persons[i].name,
                persons[i].age);
    }
    return 0;
}

int main(int argc, char **argv)
{
    if( write_to_file()){
        printf("write fail\n");
        return -1;
    }

    if(read_from_file()) {
        printf("read fail\n");
        return -1;
    }
    return 0;
}

