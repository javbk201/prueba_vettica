#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void blabla (char *str1, int s){
	char t[] = ",";
	char *token;
	char c = 0;
	token = strtok(str1, t);
	while(token != NULL){
		c = c + 1;
		if (c == 3){
			printf("%s\r\n", token);	
		}
		token = strtok(NULL, t);
	}
}

int main(){
	FILE *archivo = NULL;
	char buff [50] = {0};
	char buffer[50] = {0};
	char len;
	archivo = fopen("datos.txt", "r");
	
	printf("a. Listar datos ordenados por apellido\r\n");
	printf("b. Listar datos ordenados por edad\r\n");
	printf("c. Escribir datos ordenados en un archivo nuevo\r\n");
	printf("d. Hacer una busqueda binaria\r\n\n");
	
	printf(">>Digite una opcion:  \r\n");
	
	if(archivo != NULL){
		while(feof(archivo) == 0){
			fgets(buff, sizeof(buff), archivo);
			len = strlen(buff);
			strcpy(buffer, buff);
			if(buffer != NULL && len > 1){
				blabla(buffer, len);
			}
		}
		system("PAUSE");
	}
	else{
		printf("Error abriendo el archivo");
	}
	fclose(archivo);
	return(0);
}
