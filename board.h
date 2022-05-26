/* 
 * board.h - header file for Sudoku board module
 *
 * A "board" is a
 *  set of counters, each distinguished by an 
 * integer key. It's a set - each key can only occur once in the set 
 * - but instead of storing (key,item) pairs, it tracks a counter 
 * for each key.  It starts empty. Each time `counters_add` is 
 * called on a given key, that key's counter is incremented. The 
 * current counter value can be retrieved by asking for the relevant 
 * key.
 * 
 * CS50
 */