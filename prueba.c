#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Person{
   char  name[50];
   char  last[50];
   char  age[50];
   char  email[100];
}  Person;

// longitud de la fila
const int ROW_LENGHT = 4; 

/* Hace split por "," para obtener cada campo y lo devuelve como una estructura
 * de tipo Person */
Person getrow(char* line){
    const char* field;
    int indexHelper = 0; // variable axuliar para mapear el indice con el campo en la estructura
    struct Person person; 

    for (field = strtok(line, ","); field && *field; field = strtok(NULL, ",\n")) {
        int index = indexHelper % ROW_LENGHT; // devolvera 0, 1, 2 = name, age, email
        if(index == 0) 
          strcpy(person.name, field);
        if(index == 1) 
          strcpy(person.last, field);
        if(index == 2) 
          strcpy(person.age, field);
        if(index == 3) 
          strcpy(person.email, field);

        // aumenta el auxiliar para obtener el siguiente campo en la fila
        indexHelper++;
    }

    return person;
}

static int myCompare(const void* a, const void* b) 
{ 
  
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 
  
// Function to sort the array 
void sort(const char* arr[], int n) 
{ 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(arr, n, sizeof(const char*), myCompare); 
} 

const int PERSONS_LENGTH = 100;

int main( ) {
    // TODO: usar arrays dinamicos en lugar de estaticos si hay tiempo 
    struct Person persons[PERSONS_LENGTH]; 
    int i,j, n = 0;
	const char* arr[5];
	char control;
	
    FILE* stream = fopen("datos.txt", "r");
    char line[1024];
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);
        persons[i] = getrow(tmp);
        // resetea variable temporal
        free(tmp);
        i++;
    }
    fclose(stream);
    
    LABEL:
	    printf("a. Listar datos ordenados por apellido\r\n");
		printf("b. Listar datos ordenados por edad\r\n");
		printf("c. Escribir datos ordenados en un archivo nuevo\r\n");
		printf("d. Hacer una busqueda binaria\r\n\n");
		
		printf(">>Digite una opcion:  \r\n");
		
		scanf("%s", &control);
	
	printf("\n");
	
	if(control == 'a'){
		printf("Los datos se organizaran por apellido");
			for (i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++) {
				arr[i] = persons[i].last;
		    }
				n = sizeof(arr) / sizeof(arr[0]);
    			sort(arr, n+1);
    			
    		for(i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++){
		    	for (j = 0; j < n+1; j++){
		    		if(arr[i] == persons[j].last){
				    	  printf( "name: %s\n", persons[j].name);
				          printf( "lastname: %s\n", persons[j].last);
				          printf( "age: %s\n", persons[j].age);
				          printf( "email: %s\n", persons[j].email);
				          printf( "----------------------------------\r\n");
						}
				}
		    }
		goto LABEL;    
	}
	if(control == 'b'){
		printf("Los datos se organizaran por edad");
	    for (i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++) {
					arr[i] = persons[i].age;
			  	}
			n = sizeof(arr) / sizeof(arr[0]);
		    sort(arr, n+1);
				    
		    for(i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++){
		    	for (j = 0; j < n+1; j++){
		    		if(arr[i] == persons[j].age){
				    	  printf( "name: %s\n", persons[j].name);
				          printf( "lastname: %s\n", persons[j].last);
				          printf( "age: %s\n", persons[j].age);
				          printf( "email: %s\n", persons[j].email);
				          printf( "----------------------------------\r\n");
						}
				}
			}
		goto LABEL;
	}
	if (control == 'c'){
		FILE* stream = fopen ("datos_organizados.txt", "Wt");
		if(stream != NULL){
			for (i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++) {
				arr[i] = persons[i].last;
		    }
		n = sizeof(arr) / sizeof(arr[0]);
    	sort(arr, n+1);
    			
    	for(i = 0; i < PERSONS_LENGTH && persons[i].name[0] != '\0'; i++){
		   	for (j = 0; j < n+1; j++){
		   		if(arr[i] == persons[j].last){
		    	  fprintf(stream, "%s,", persons[j].name);
		          fprintf(stream, "%s,", persons[j].last);
		          fprintf(stream, "%s,", persons[j].age);
		          fprintf(stream, persons[j].email);
				}
			}
		  }
		}
		else{
			printf("Error al abrir el archivo\r\n");
		}
		fclose(stream);
		goto LABEL;   
	}
	
   
   return 0;
}
