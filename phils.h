#ifndef PHILS_H
# define PHILS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define RED        "\x1B[31m"
# define WTH        "\x1B[38m"
# define GRN        "\x1B[32m"
# define YEL        "\x1B[33m"
# define BLU        "\x1B[34m"
# define MAG        "\x1B[35m"
# define CYN        "\x1B[36m"
# define RESET      "\x1B[0m"

typedef struct s_param {
	time_t			start;
	int				numOfFil;
	int				timeToDie;
	int				timeToEatt;
	int				timeToSleep;
	int				fullness;
	pthread_mutex_t	forks[200];
}					t_param;

typedef struct s_check {
	short int		philsAreAlive;
	pthread_mutex_t	utils[200];
}					t_check;

typedef struct s_fil {
	int				id;
	int				left;
	int				right;
	t_param			*param;
	t_check			*check;
	time_t			toLive;
	int				countOfEat;
	short int		isFull;
	short int		nowIsEating;
}					t_fil;

int		ft_atoi(const char *str);
int		parser(t_param *param, t_check *check, char **av, int ac);
time_t	get_time(void);
void	message(t_fil *fil, const char *str, int flag);
int		fullnessCheck(t_fil *fil, int i);
void	*monitoring(void *oneFil);
int		initFils(t_fil *fil, t_check *check, t_param *param);

#endif
