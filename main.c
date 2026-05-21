while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);
		read_bytes = _getline(&line, &len, stdin);
		if (read_bytes <= 0)
		{
			if (isatty(STDIN_FILENO) && read_bytes == 0)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			free_env();
			exit(last_status);
		}
		if (line[read_bytes - 1] == '\n')
			line[read_bytes - 1] = '\0';
		
		parse_command(line, args);
		
		
		expand_variables(args, last_status);
	

		execute_command(args, av, line, &last_status);
	}
