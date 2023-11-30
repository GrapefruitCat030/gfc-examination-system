# 编译器设置
CXX = g++
CXXFLAGS = -std=c++2a -Wall -g3

# 源文件和头文件路径
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# 获取所有源文件和对应的目标文件
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(SRCS))

# 可执行文件名
TARGET = $(BUILD_DIR)/exam_system

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 生成目标文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

run:
	@./build/exam_system