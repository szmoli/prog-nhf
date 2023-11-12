/**
 * @brief Gráfkezelő program
 */

#define SDL_MAIN_HANDLED

#include "SDL2_gfxPrimitives.h"
#include "debugmalloc.h"
#include "typedefs.h"
#include "linked_list.h"
#include "dynamic_array.h"
#include "graph.h"
#include "graphics.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int main(void) {
    /**
     * @brief A gráfpont azonosító.
     * @details Minden pontnak egyedi azonosítója van. Az azonosító mindig egyel növekszik, amikor egy új pontot hozunk létre, így gyakorlatilag a létrehozható pontjainknak felső határa 4294967295, azaz az unsigned int felső határa. 
     */
    unsigned int id = 0;

    /**
     * @brief Lista az összes létező gráfpontról (Vertex_Data).
     * @details Amikor egy új pontot hozunk létre, azt ebben a listában tartjuk nyilván. Ha a felhasználó kitöröl egy pontot, az a listából is törlődik. A gráfot tároló adatstruktúra ennek a listának a tárolt pontjaira mutat, ha kitörlünk egy pontot, akkor azt a gráf adatstruktúrájából is kitöröljük.
     */
    List *vertexes = new_list();

    /**
     * @brief Egy dinamikus tömb, ami az összes ponthoz tartozó szomszédosságokat tárolja.
     * @details Amikor egy új pontot hozunk létre, ehhez a tömbhöz hozzáadunk egy láncolt listát, aminek a legelején egy mutató van a létrehozott pontra. Ha ezt a pontot összekötjük egy másikkal, akkor mindkettőjük listájához hozzáadunk egy mutatót a másik pontra. Így tárolódnak el a szomszédosságok.
     */
    Array *neighbour_arr = new_array();

    SDL_Window *window = NULL;
    SDL_Surface *window_surface = NULL;
    SDL_Renderer *renderer = NULL;
    bool running = true;

    if (!config_sdl(&window, &window_surface, &renderer)) {
        fprintf(stderr, "%s: config failed\n\n", __func__);
        return -1;
    }

    while (running) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        window_surface = SDL_GetWindowSurface(window);

                        //printf("resizing: %dx%d\n", window_surface->w, window_surface->h);
                        break;

                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                quit_sdl(&window, &renderer, &running);
                break;
            default:
                SDL_SetRenderDrawColor(renderer, 247, 243, 243, 255);
                SDL_RenderClear(renderer);
                SDL_RenderPresent(renderer);
                break;
        }
    }

    new_vertex(neighbour_arr, vertexes, new_vertex_data(&id));
    new_vertex(neighbour_arr, vertexes, new_vertex_data(&id));
    new_vertex(neighbour_arr, vertexes, new_vertex_data(&id));
    //new_vertex(neighbour_arr, vertexes, new_vertex_data(&id));

    // list_clear(neighbour_arr->array[0]);
    print_list(neighbour_arr->array[0], VERTEX_DATA_POINTER);
    print_list(neighbour_arr->array[1], VERTEX_DATA_POINTER);    
    print_list(neighbour_arr->array[2], VERTEX_DATA_POINTER);    
    printf("neighbour list printed\n\n");


    print_list(vertexes, VERTEX_DATA);
    printf("vertexes printed\n\n");

    //destroy_list(neighbour_arr->array[0]);
    print_list(vertexes, VERTEX_DATA);
    //printf("%p\n", vertexes->head_node->data);


    destroy_array(neighbour_arr, LINKED_LIST, false);
    destroy_list(vertexes, true);
    printf("program vege\n");
    return 0;
}