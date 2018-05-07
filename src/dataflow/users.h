/*
 * Copyright 2018 WebAssembly Community Group participants
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// DataFlow IR is an SSA representation. It can be built from the main
// Binaryen IR.
//
// THe main initial use case was an IR that could easily be converted to
// Souper IR, and the design favors that.
//

#ifndef wasm_dataflow_users_h
#define wasm_dataflow_users_h

#include "dataflow/graph.h"

namespace wasm {

namespace DataFlow {

// Calculates the users of each node.
//   users[x] = { y, z, .. }
// where y, z etc. are nodes that use x, that is, x is in their
// values vector.
class Users : public std::unordered_map<DataFlow::Node*, std::unordered_set<DataFlow::Node*>> {
public:
  void build(Graph& graph) {
    for (auto& node : graph.nodes) {
      for (auto* value : node->values) {
        (*this)[value].insert(node.get());
      }
    }
  }

  Index getNumUsers(Node* node) {
    auto iter = find(node);
    if (iter == end()) return 0;
    return iter->second.size();
  }
};

} // namespace DataFlow

} // namespace wasm

#endif // wasm_dataflow_users
