# NOTA: Sujeito a alterações. Vou tentar otimizar isto, para que não fique parecido ao chat
# Eu tive de o usar para perceber a cena da linkagem, e maneira que consegui que funcionasse 
# até agora foi ter os testes em separado
TESTS = test_data test_list test_serialization # Em comentário porque ainda não está implementado

#Variaveis
OBJECTS = data.o list-utils-private.o list.o serialization.o
TEST_OBJECTS = test-data.o test-list.o test-serialization.o

# Diretórios
OBJ_dir = object
BIN_dir = binary
include_DIR = includelude
TEST_DIR = tests

# Dependências - a rever se faz sentido ou não
# data.o = 
# list.o = data.h
# serialization.o = data.h list.h
# test_data.o = data.h
# test_list.o = data.h list.h
# test_serialization.o = data.h list.h serialization.h

# Flags e compilador
CFLAGS = -Wall -I $(include_DIR)
CC = gcc

# # Alvo 
# out: $(TESTS)

# test_data: $(OBJ_dir)/test_data.o $(OBJ_dir)/data.o
# 	$(CC) -o $(BIN_dir)/$@ $^

# test_list: $(OBJ_dir)/test_list.o $(OBJ_dir)/list.o $(OBJ_dir)/data.o
# 	$(CC) -o $(BIN_dir)/$@ $^

# # Em comentário porque ainda não está implementado
# # test_serialization: $(OBJ_dir)/test_serialization.o $(OBJ_dir)/serialization.o $(OBJ_dir)/list.o $(OBJ_dir)/data.o
# # 	$(CC) $^ -o $(BIN_dir)/$@

# # Regras para ficheiros .o
# $(OBJECTS)/%.o: source/%.c $($@)
# 	 $(CC) $(CFLAGS) -o $@ -c $<

# $(TEST_OBJECTS)/%.o: tests/%.c $($@)
# 	 $(CC) $(CFLAGS) -o $@ -c $<

all: data.o list-utils-private.o list.o test_data.o test_list.o test_serialization.o

data.o: source/data.c include/data.h
	gcc -c source/data.c -I include -Wall -o object/data.o 

list-utils-private.o: source/list-utils-private.c include/list-utils-private.h include/list-private.h include/data.h
	gcc -c source/list-utils-private.c -I include -Wall -o object/list-utils-private.o   

list.o: source/list.c include/list.h include/data.h include/list-utils-private.h
	gcc -c source/list.c -I include -Wall -o object/list.o   

# serialization.o: source/serialization.c include/serialization.h include/list.h include/data.h
# 	gcc -c source/serialization.c -I include -Wall -o object/serialization.o   

test_data.o: tests/test_data.c include/data.h
	gcc -c tests/test_data.c -I include -Wall -o object/test_data.o   

test_list.o: tests/test_list.c include/list.h
	gcc -c tests/test_list.c -I include -Wall -o object/test_list.o  

# test_serialization.o: tests/test_serialization.c include/serialization.h
# 	gcc -c tests/test_serialization.c -I include -Wall -o object/test_serialization.o  






 


# Regra para limpar ficheiros .o e executáveis
clean: 
	rm -f $(OBJ_dir)/*.o
	rm -f $(BIN_dir)/*

