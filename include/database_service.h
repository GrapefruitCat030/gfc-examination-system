#pragma once


// 数据库服务类使用Repository模式
class DataBaseService {
private:
    std::unique_ptr<IDataBaseRepository> userRepository;

public:
    void SetUserRepository(std::unique_ptr<IDataBaseRepository> repository) {
        userRepository = std::move(repository);
    }

    void Connect() {
        // 连接数据库的逻辑
    }

    void Disconnect() {
        // 断开数据库连接的逻辑
    }

    void CreateItem() {
        userRepository->CreateItem();
    }

    void FindItem() {
        userRepository->FindItem();
    }

    void UpdateItem() {
        userRepository->UpdateItem();
    }

    void DeleteItem() {
        userRepository->DeleteItem();
    }
};