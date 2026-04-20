CC = clang
CFLAGS = -I./include -fPIC -O3
LDFLAGS = -lm -lpthread -ldl

# Diretórios
SRC_DIR = src
MOD_DIR = modules
BIN_DIR = .

# Alvos
all: kynto core_modules

kynto: $(SRC_DIR)/ckynto.c
	$(CC) $(SRC_DIR)/ckynto.c -o $(BIN_DIR)/kynto $(LDFLAGS) $(CFLAGS)

core_modules:
	$(CC) -shared $(CFLAGS) $(MOD_DIR)/k_net.c -o k_net.so
	$(CC) -shared $(CFLAGS) $(MOD_DIR)/k_crypt.c -o k_crypt.so
	$(CC) -shared $(CFLAGS) $(MOD_DIR)/k_math.c -o k_math.so

clean:
	rm -f kynto *.so
