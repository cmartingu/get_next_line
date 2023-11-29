#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char *ft_realloc(char *aux, int tam)
{
	char	*sol;
	int		i;
	char	*aux_aux;

	if (!aux)
		aux = strdup("");
	aux_aux = aux;
	tam++;
	sol = malloc(tam + 1);
	if (!sol)
		return (NULL);
	sol[tam] = '\0';
	i = 0;
	while (i < (tam - 1) && *aux)
	{
		sol[i] = *aux;
		aux++;
		i++;
	}
	free(aux_aux);
	return (sol);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*sol;
	char		*aux_buff;
	char		*aux_final_buff;
	int			cont;
	int			numbytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!buff) // crear asignar NULL a sol, crear buffer e iniciar el contador a o;
	{
		buff = malloc(BUFFER_SIZE + 1);
		buff[BUFFER_SIZE] = '\0';
		sol = NULL;
		cont = 0;
	}
	else
	{
		if (!strchr(buff, '\n')) // No hay \n dentro de buff por lo que guardamos el contenido de buffer en sol,
		{						 //Liberamos buffer e iniciamos el contador en el tamaño de sol
			sol = strdup(buff);
			cont = strlen(sol) - 1;
			free(buff);
			buff = malloc(BUFFER_SIZE + 1);
			buff[BUFFER_SIZE] = '\0';
		}
		else					//Hay \n en el buffer. guardamos en sol lo que hay hasta \n y
		{						//modificamos el buffer para que tenga solo el resto
			sol = NULL;
			cont = 0;
			while (buff[cont] != '\n')
			{
				sol = ft_realloc(sol, cont);
				sol[cont] = buff[cont];
				cont++;
			}
			sol = ft_realloc(sol, cont);
			sol[cont] = buff[cont];
			aux_buff = strdup(strchr(buff, '\n') + 1);
			free(buff);
			buff = aux_buff;
			return (sol);
		}
	} // Ya solo queda leer hasta encontrar un \n o llegar al final del archivo
	numbytes = read(fd, buff, BUFFER_SIZE);
	if (numbytes <= 0)
		return (free(buff), sol);
	aux_final_buff = NULL;
	while (numbytes > 0)
	{
		aux_buff = buff;
		while (*buff)
		{
			sol = ft_realloc(sol, cont);
			sol[cont] = *buff;
			if (*buff == '\n')
			{
				if (*(buff + 1) != '\0')
					aux_final_buff = strdup(buff + 1);
				buff = aux_buff;
				free(buff);
				buff = aux_final_buff;
				return (sol);
			}
			cont++;
			buff++;
		}
		buff = aux_buff;
		free(buff);
		numbytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (sol);
}

int main(void)
{
	int fd = open("prueba.txt", O_RDONLY);
	char *c = get_next_line(fd);
	char *f = get_next_line(fd);
	printf("%s", c);
	printf("%s", f);
	free(c);
	free(f);
	return (0);
}