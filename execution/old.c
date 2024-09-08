// void	exec_cmdlist(t_tokenlist **cmdlist, bool with_pipe)
// {
// 	t_tokenlist	*redirlist;
// 	int			infilefd;
// 	int			outfilefd;

// 	redirlist = extract_redirs(&cmdlist);
// 	infilefd = get_infilefd(redirlist);
// 	if (infilefd == -1)
// 	{
// 		set_exit_status(1);
// 		free_tokenlist(redirlist);
// 		return ;
// 	}
// 	outfilefd = get_outfilefd(redirlist);
// 	if (outfilefd == -1)
// 	{
// 		set_exit_status(1);
// 		free_tokenlist(redirlist);
// 		return ;
// 	}
// 	free_tokenlist(redirlist);
// }
