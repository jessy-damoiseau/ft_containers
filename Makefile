################################################################################
#                               Filename output                                #
################################################################################

NAME		=	ft_containers

################################################################################
#                         Sources and objects directories                      #
################################################################################

SRCS_DIR	=	.
OBJS_DIR	=	objs\&deps
HEADERS		= 	.

################################################################################
#                               Sources filenames                              #
################################################################################

SRCS		=	main_ft.cpp


################################################################################
#                              Commands and arguments                          #
################################################################################

XXCC			=	c++
XXCFLAGS		=	-Wall -Wextra -Werror -std=c++98
RM				=	rm -rf

################################################################################
#                                 Defining colors                              #
################################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m
_NC			=	\033[0m

################################################################################
#                                  Compiling                                   #
################################################################################

SRCS_DEP	=	$(patsubst %.cpp,%.d,$(SRCS))
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

-include $(SRCS_DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(SRCS_DEPS)
	@ echo "\t$(_YELLOW) compiling... $*.cpp$(_NC)"
	$(XXCC) $(XXCFLAGS) -MMD -MP -c $< -o $@ -I $(HEADERS)

################################################################################
#                                    Rules	                                   #
################################################################################

all:	$(NAME)

init:
	@ if test -f $(NAME);\
	then echo "$(_CYAN)[program already created]$(_NC)";\
	else echo "$(_YELLOW)[Initialize program]$(_NC)";\
	fi
	$(shell mkdir -p $(OBJS_DIR))

$(NAME):	init $(OBJS)
	@ echo "\t$(_YELLOW)[Creating program]$(_NC)"
	$(XXCC) $(OBJS) -o $(NAME)
	@ echo "$(_GREEN)[program created & ready]$(_NC)"

clean:
	echo "$(_RED)[cleaning up .out & objects files]"
	$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
	@ echo "$(_RED)[cleaning up .out, objects & library files]$(_NC)"
	$(RM) $(NAME)

re:	fclean all

script:
	sh script_FtToStd.sh

clean_script:
	$(RM) srcs/main_std.cpp

.SILENT:
		all

.PHONY: all clean fclean re bonus script