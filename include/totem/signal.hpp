#pragma once

#include <unordered_map>
#include <cstddef>
#include <string_view>
#include <string>
#include <functional>

namespace ecf {
	template<typename... Args>
	class Signal {
	public:
		using Subscriber = std::function<void(Args...)>;

		void connect(std::string_view name, Subscriber sub) {
			this->mSubscribers->emplace(name, std::move(sub));
		}

		void disconnect(std::string_view name) {
			if (this->mSubscribers.contains(name)) {
				this->mSubscribers.erase(name);
			}
		}

		void emit(Args... args) {
			for (auto& [id, sub] : this->mSubscribers) {
				sub(args...);
			}
		}
	private:
		std::unordered_map<std::string, Subscriber> mSubscribers;
	};
}
