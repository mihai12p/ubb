from typing import Dict, List, Optional, Tuple

from pydantic import BaseModel

from grammar import Grammar, Production


class State(BaseModel):
    production: Production
    lookahead: List[str]
    point_idx: int = 0

    def __eq__(self, other: "State") -> bool:
        return (
            self.production == other.production
            and self.lookahead == other.lookahead
            and self.point_idx == other.point_idx
        )

    def __hash__(self) -> int:
        return hash((self.production, tuple(self.lookahead), self.point_idx))


class LR1Parser:
    def __init__(self, grammar: Grammar):
        self._grammar = grammar
        self._first_table = self._grammar.first_table()
        self._all_symbols = list(
            filter(
                lambda x: x != self._grammar.starting_symbol,
                self._grammar.non_terminals + self._grammar.terminals,
            )
        )
        print(self._all_symbols)
        self._canon_collection, self._table = self._build_canon_collection()
        for idx, canon_collection_elem in enumerate(self._canon_collection):
            print(f"I{idx}: {canon_collection_elem}")
        for idx, action in self._table.items():
            print(f"I{idx}: {action}")

    def _build_closure(self, state: State) -> List[State]:
        closure = []
        new_items = [state]
        while len(new_items) > 0:
            closure += new_items
            unverified_items = len(new_items)
            new_items = []
            for item in closure[-unverified_items:]:
                transition = item.production.transition
                if item.point_idx >= len(transition):
                    continue
                next_symbol = transition[item.point_idx]
                if next_symbol not in self._grammar.non_terminals:
                    continue
                after_next_symbol = (
                    []
                    if item.point_idx + 1 >= len(transition)
                    else [transition[item.point_idx + 1]]
                    if transition[item.point_idx + 1] in self._grammar.terminals
                    else self._first_table[transition[item.point_idx + 1]]
                )
                next_lookahead = (
                    item.lookahead
                    if len(after_next_symbol) == 0
                    else after_next_symbol
                    if item.lookahead == ["$"]
                    else list(set(item.lookahead + after_next_symbol))
                )
                for production in self._grammar.productions[next_symbol]:
                    new_item = State(
                        production=production,
                        lookahead=next_lookahead,
                    )
                    if new_item not in closure:
                        new_items.append(new_item)
        return closure

    def _build_canon_collection(
        self,
    ) -> (List[List[State]], Dict[int, Dict[str, Optional[Tuple[str, Optional[int]]]]]):
        starting_symbol = self._grammar.starting_symbol
        canon_collection = [
            self._build_closure(
                State(
                    production=self._grammar.productions[starting_symbol][0],
                    lookahead=["$"],
                )
            )
        ]
        table: Dict[int, Dict[str, Optional[Tuple[str, Optional[int]]]]] = {}
        idx = 0
        while idx < len(canon_collection):
            states = canon_collection[idx]
            table[idx] = {symbol: None for symbol in self._all_symbols}
            table[idx]["$"] = None
            for state in states:
                transition = state.production.transition
                if state.point_idx == len(transition):
                    if state.production.non_terminal == starting_symbol:
                        table[idx]["$"] = ("accept", None)
                    else:
                        for lookahead in state.lookahead:
                            if table[idx][lookahead] is not None:
                                if table[idx][lookahead][0] == "shift":
                                    raise ValueError(
                                        "The grammar is not LR(1)! There is a shift / reduce conflict!"
                                    )
                                else:
                                    raise ValueError(
                                        "The grammar is not LR(1)! There is a reduce / reduce conflict!"
                                    )
                            table[idx][lookahead] = ("reduce", state.production.idx)
                else:
                    symbol = state.production.transition[state.point_idx]
                    goto = self._build_closure(
                        State(
                            production=state.production,
                            lookahead=state.lookahead,
                            point_idx=state.point_idx + 1,
                        )
                    )
                    if table[idx][symbol] is not None:
                        if table[idx][symbol][0] == "reduce":
                            raise ValueError(
                                "The grammar is not LR(1)! There is a shift / reduce conflict!"
                            )
                        elif idx < table[idx][symbol][1]:
                            canon_collection[table[idx][symbol][1]] += goto
                        else:
                            raise ValueError("There was an error in the algorithm!")
                    elif goto in canon_collection:
                        table[idx][symbol] = ("shift", canon_collection.index(goto))
                    else:
                        table[idx][symbol] = ("shift", len(canon_collection))
                        canon_collection.append(goto)

            idx += 1
        return canon_collection, table

    def parse_string(self, string: str):
        work_stack = ["$", 0]
        input_lane = list(string) + ["$"]
        output_lane = []
        while True:
            print(work_stack, input_lane, output_lane)
            action = self._table[work_stack[-1]][input_lane[0]]
            if action is None:
                raise ValueError("The string is not accepted by the grammar!")
            elif action[0] == "accept":
                break
            elif action[0] == "shift":
                work_stack.append(input_lane.pop(0))
                work_stack.append(action[1])
            elif action[0] == "reduce":
                production = self._grammar.raw_productions[action[1]]
                for _ in range(2 * len(production.transition)):
                    work_stack.pop()
                work_stack.append(production.non_terminal)
                if work_stack[-2] == "$":
                    work_stack.pop()
                if self._table[work_stack[-2]][work_stack[-1]] is None:
                    raise ValueError("The string is not accepted by the grammar!")
                work_stack.append(self._table[work_stack[-2]][work_stack[-1]][1])
                output_lane.insert(0, action[1])
        print("The string is accepted by the grammar!")
