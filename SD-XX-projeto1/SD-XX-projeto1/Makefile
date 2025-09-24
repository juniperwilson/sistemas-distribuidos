# NOTA: Sujeito a alterações. Vou tentar otimizar isto, para que não fique parecido ao chat
# Eu tive de o usar para perceber a cena da linkagem, e maneira que consegui que funcionasse 
# até agora foi ter os testes em separado
TESTS = test_data test_list test_serialization # Em comentário porque ainda não está implementado

# Diretórios
OBJ_dir = object
BIN_dir = binary
INC_DIR = include

# Dependências - a rever se faz sentido ou não
data.o = 
list.o = data.h
serialization.o = data.h list.h
test_data.o = data.h
test_list.o = data.h list.h
test_serialization.o = data.h list.h serialization.h

# Flags e compilador
CFLAGS = -Wall -I $(INC_DIR)
CC = gcc

# Alvo 
out: $(TESTS)

test_data: $(OBJ_dir)/test_data.o $(OBJ_dir)/data.o
	$(CC) -o $(BIN_dir)/$@ $^

test_list: $(OBJ_dir)/test_list.o $(OBJ_dir)/list.o $(OBJ_dir)/data.o
	$(CC) -o $(BIN_dir)/$@ $^

# Em comentário porque ainda não está implementado
test_serialization: $(OBJ_dir)/test_serialization.o $(OBJ_dir)/serialization.o $(OBJ_dir)/list.o $(OBJ_dir)/data.o
	$(CC) $^ -o $(BIN_dir)/$@

# Regras para ficheiros .o
$(OBJ_dir)/%.o: source/%.c $($@)
	 $(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_dir)/%.o: tests/%.c $($@)
	 $(CC) $(CFLAGS) -o $@ -c $<

# Regra para limpar ficheiros .o e executáveis
clean: 
	rm -f $(OBJ_dir)/*.o
	rm -f $(BIN_dir)/*

