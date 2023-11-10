/**
 * @file graph.c
 * @author Szmoleniczki Ákos
 * @brief Ez a fájl a gráfműveletekhez tartozó függvényeket tartalmazza.
 * @version 0.1
 * @date 2023-11-10
 */

#include "typedefs.h"
#include "linked_list.h"
#include "dynamic_array.h"
#include "debugmalloc.h"
#include <memory.h>
#include <stdlib.h>

/**
 * @todo Befejezni ezt a függvényt. Kijavítani a hibákat. Dokumentációt írni.
 * @brief 
 * 
 * @param neighbour_arr 
 * @param vertexes 
 * @param data 
 */
void new_vertex(Array *neighbour_arr, List *vertexes, Vertex_Data *data) {
    Node *node = new_node(data);
    Vertex_Data **orig_data = (Vertex_Data **) malloc(sizeof(Vertex_Data *));
    orig_data = &(node->data);
    Node *neighbour_node = new_node(orig_data);
    List *neighbour_list = new_list();
    
    list_push(vertexes, node);
    list_push(neighbour_list, neighbour_node);
    array_push(neighbour_arr, neighbour_list);
}

int main(void) {
    /**
     * @var unsigned int id
     * @brief A gráfpont azonosító.
     * @details Minden pontnak egyedi azonosítója van. Az azonosító mindig egyel növekszik, amikor egy új pontot hozunk létre, így gyakorlatilag a létrehozható pontjainknak felső határa 4294967295, azaz az unsigned int felső határa. 
     */
    unsigned int id = 0;

    /**
     * @var List *vertexes
     * @brief Lista az összes létező gráfpontról.
     * @details Amikor egy új pontot hozunk létre, azt ebben a listában tartjuk nyilván. Ha a felhasználó kitöröl egy pontot, az a listából is törlődik. A gráfot tároló adatstruktúra ennek a listának a tárolt pontjaira mutat, ha kitörlünk egy pontot, akkor azt a gráf adatstruktúrájából is kitöröljük.
     */
    List *vertexes = new_list();

    /**
     * @var Array *neighbour_arr
     * @brief Egy dinamikus tömb, ami az összes ponthoz tartozó szomszédosságokat tárolja.
     * @details Amikor egy új pontot hozunk létre, ehhez a tömbhöz hozzáadunk egy láncolt listát, aminek a legelején egy mutató van a létrehozott pontra. Ha ezt a pontot összekötjük egy másikkal, akkor mindkettőjük listájához hozzáadunk egy mutatót a másik pontra. Így tárolódnak el a szomszédosságok.
     */
    Array *neighbour_arr = new_array();

    new_vertex(neighbour_arr, vertexes, new_vertex_data(&id));

    // print_list(vertexes, VERTEX_DATA);

    destroy_list(vertexes);
    destroy_array(neighbour_arr);
    
    return 0;
}