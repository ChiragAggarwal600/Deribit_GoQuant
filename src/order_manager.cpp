#include "order_manager.hpp"
#include "utils.hpp"
#include <nlohmann/json.hpp>

// function to place an order using the access token
// order_manager.cpp
std::string OrderManager::placeOrder(const std::string& symbol, const std::string& type, double amount, double price, const std::string& orderType) {
    std::string access_token = UtilityNamespace::authenticate();
    std::string url = "https://test.deribit.com/api/v2/private/" + type;  // 'buy' or 'sell'

    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 2},
        {"method", "private/" + type},
        {"params", {
            {"instrument_name", symbol},
            {"amount", amount},
            {"type", orderType},
            {"price", price}
        }}
    };

    // Authorization header
    std::string authHeader = "Authorization: Bearer " + access_token;

    // Send POST request with authorization header
    return UtilityNamespace::sendPostRequestWithAuth(url, payload.dump(), authHeader);
}

// function to cancel an order
std::string OrderManager::cancelOrder(const std::string& order_id) {
    std::string access_token = UtilityNamespace::authenticate();
    std::string url = "https://test.deribit.com/api/v2/private/cancel";
    
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 2},
        {"method", "private/cancel"},
        {"params", {
            {"order_id", order_id}
        }}
    };

    std::string authHeader = "Authorization: Bearer " + access_token;
    return UtilityNamespace::sendPostRequestWithAuth(url, payload.dump(), authHeader);
}

// function to modify an order
std::string OrderManager::modifyOrder(const std::string& order_id, double new_amount, double new_price) {
    std::string access_token = UtilityNamespace::authenticate();
    std::string url = "https://test.deribit.com/api/v2/private/edit";

    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 2},
        {"method", "private/edit"},
        {"params", {
            {"order_id", order_id},
            {"amount", new_amount},
            {"price", new_price}
        }}
    };

    std::string authHeader = "Authorization: Bearer " + access_token;
    return UtilityNamespace::sendPostRequestWithAuth(url, payload.dump(), authHeader);
}

// function to get order book
std::string OrderManager::getOrderBook(const std::string& symbol) {
    std::string url = "https://test.deribit.com/api/v2/public/get_order_book";
    std::string payload = "{\"jsonrpc\":\"2.0\", \"method\":\"public/get_order_book\", \"params\":{\"instrument_name\":\"" + symbol + "\"}, \"id\":4}";
    return UtilityNamespace::sendPostRequest(url, payload);
}

// function to get current positions
std::string OrderManager::getCurrentPositions(const std::string& currency) {
    std::string access_token = UtilityNamespace::authenticate();
    std::string url = "https://test.deribit.com/api/v2/private/get_positions";

    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 4},
        {"method", "private/get_positions"},
        {"params", {
            {"currency", currency},
            {"kind", "future"}
        }}
    };

    std::string authHeader = "Authorization: Bearer " + access_token;
    return UtilityNamespace::sendPostRequestWithAuth(url, payload.dump(), authHeader);
}
