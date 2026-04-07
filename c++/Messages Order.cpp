#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Message {
private:
    string text_;
    int id_; // Stores the creation sequence number
public: 
    Message() : text_(""), id_(0) {}
    
    // Custom constructor to store text and its relative order
    Message(const string& text, int id) : text_(text), id_(id) {}

    const string& get_text() {
        return text_;
    }

    // Overload < operator so sort() knows to order by id_
    bool operator < (const Message& other) {
        return this->id_ < other.id_;
    }
};

class MessageFactory {
private:
    int current_id; // Counter to assign unique IDs in sequence
public:
    MessageFactory() : current_id(0) {}

    Message create_message(const string& text) {
        // Create the message with the current ID, then increment it
        return Message(text, current_id++);
    }
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}
