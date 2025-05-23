#pragma once

#include <string>
#include <variant>
#include <vector>

using NodePK = unsigned int;
using EdgePK = unsigned int;
using AdjList = std::vector<std::vector<EdgePK>>;

class Data;

using DataStringType = std::string;
using DataIntType = long long;
using DataRealType = double;
using DataArrayType = std::vector<Data>;

using DataVariant = std::variant<DataStringType, DataIntType, DataRealType, DataArrayType>;
class Data
	: public DataVariant
{
public:
	using base = DataVariant;
	using base::base;
	using base::operator=;
};


// Operator "<<" overloading for Data
// std::ostream& operator<<(std::ostream& os, const Data& data) {
//     std::visit([&os](const auto& value) {
//         using Type = std::decay_t<decltype(value)>;
//         if constexpr (std::is_same_v<Type, DataArrayType>) {
//             os << "[ ";
//             for (const auto& elem : value) {
//                 os << elem << " ";  // Recursively calls operator<<
//             }
//             os << "]";
//         } else {
//             os << value;
//         }
//     }, data.variant);
//     return os;
// }
