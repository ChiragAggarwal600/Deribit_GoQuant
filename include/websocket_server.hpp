#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <mutex>

typedef websocketpp::server<websocketpp::config::asio> server;

class WebSocketServer {
public:
    WebSocketServer();
    void startServer(uint16_t port);
    void stopServer();
    void sendOrderbookUpdate(const std::string& symbol, const nlohmann::json& orderbook);

private:
    void onOpen(websocketpp::connection_hdl hdl);
    void onClose(websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);

    server m_server;
    std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> m_connections;
    std::unordered_map<std::string, std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>>> m_subscribers;
    std::thread m_serverThread;
    std::mutex m_mutex; // Mutex for thread safety
};