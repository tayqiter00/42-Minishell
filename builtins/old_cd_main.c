
// t_tokennode *create_tokennode(char *token, bool metachar)
// {
//     t_tokennode *new_tokennode;

//     new_tokennode = malloc(sizeof(t_tokennode));
//     new_tokennode->token = token;
//     new_tokennode->next = NULL;
// 	new_tokennode->is_meta_char = metachar;
//     return (new_tokennode);
// }

// static size_t	determine_copy_size(size_t original_size, size_t new_size)
// {
// 	size_t	copy_size;

// 	if (original_size < new_size)
// 		copy_size = original_size;
// 	else
// 		copy_size = new_size;
// 	return (copy_size);
// }

// // The reason I have a function to determine the copy size
// // Is because, of how ft_memcpy works,
// // It won't check for \0 or anything of that sorts,
// // it only runs until the size you specify
// // So it's crucial, that I only copy until the original data,
// // rather than going out of bound
// void	*ft_realloc(void *ptr, size_t original_size, size_t new_size)
// {
// 	void	*new_ptr;
// 	size_t	copy_size;

// 	if (!ptr)
// 		return (malloc(new_size));
// 	if (new_size == 0)
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	new_ptr = malloc(new_size);
// 	if (!new_ptr)
// 		return (NULL);
// 	copy_size = determine_copy_size(original_size, new_size);
// 	memcpy(new_ptr, ptr, copy_size);
// 	free(ptr);
// 	return (new_ptr);
// }

// int	count_2d_array_items(char **double_array)
// {
// 	int	count;

// 	count = 0;
// 	while (double_array[count])
// 		count++;
// 	return (count);
// }

// char	**clone_double_array(char **double_array)
// {
// 	int		items_count;
// 	char	**result;
// 	int		i;

// 	items_count = count_2d_array_items(double_array) + 1;
// 	result = malloc(sizeof(char *) * items_count);
// 	if (result == NULL)
// 	{
// 		printf("malloc failed for result\n");
// 		exit(-1);
// 	}
// 	i = -1;
// 	while (double_array[++i])
// 	{
// 		result[i] = ft_strdup(double_array[i]);
// 		if (result[i] == NULL)
// 		{
// 			printf("ft_strdup failed for result[%d]\n", i);
// 			exit(-1);
// 		}
// 	}
// 	result[i] = NULL;
// 	return (result);
// }

// void	free_double_array(char **double_array)
// {
// 	int	i;

// 	i = -1;
// 	while (double_array[++i])
// 		free(double_array[i]);
// 	free(double_array);
// }

// static void	add_to_envp(char ***envp, char *new_entry)
// {
// 	int		count;
// 	int		old_size;
// 	int		new_size;
// 	char	**new_envp;

// 	count = count_2d_array_items(*envp);
// 	old_size = sizeof(char *) * (count + 1);
// 	new_size = sizeof(char *) * (count + 2);
// 	new_envp = ft_realloc(*envp, old_size, new_size);
// 	if (!new_envp)
// 	{
// 		printf("ft_realloc failed for new_envp\n");
// 		exit(-1);
// 	}
// 	new_envp[count] = ft_strdup(new_entry);
// 	if (!new_envp[count])
// 	{
// 		printf("ft_strdup failed for new_envp[%d]\n", count);
// 		exit(-1);
// 	}
// 	new_envp[count + 1] = NULL;
// 	*envp = new_envp;
// }

// char	**clone_envp_with_special(char **envp)
// {
// 	char	**envp_dup;

// 	envp_dup = clone_double_array(envp);
// 	add_to_envp(&envp_dup, "?=0");
// 	return (envp_dup);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	// int	errno;
// 	char	s[PATH_MAX];
// 	char	*path = "..";
// 	t_tokennode *args = create_tokennode(path, false);

// 	envp = clone_envp_with_special(envp);
// 	// errno = 0;
// 	printf("wd before cd: %s\n", getcwd(s, PATH_MAX - 1)); 
// 	printf("$PWD before cd: %s\n", getenv("PWD"));
// 	printf("$OLDPWD before cd: %s\n", getenv("OLDPWD"));
// 	ft_cd(args, envp);
// 	printf("\n");
// 	printf("wd after cd: %s\n", getcwd(s, PATH_MAX - 1));
// 	printf("$PWD after cd: %s\n", getenv("PWD"));
// 	printf("$OLDPWD after cd: %s\n", getenv("OLDPWD"));
// 	// errno = chdir(path);
// 	// errno = cd_home(envp);
// 	// printf("errno: %d\n", errno);
// 	// printf("%s\n", getcwd(s, 100));
// 	// printf("\n");
// 	// printf("%s\n", getenv("PWD"));
// 	// printf("%s\n", getenv("OLDPWD"));
// 	return (0);
// }