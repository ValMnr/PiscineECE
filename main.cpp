#include "grman/grman.h"
#include <iostream>
#include <allegro.h>
//#include <allegro_native_dialog.h>

#include "graph.h"

int main()
{
    int ided;
    int idv;
    int som_dep, som_arr, index, poids;
    int val;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
        if(key[KEY_E])
        {
            std::cout<<"saisir index arete a supprimer"<<std::endl;
            std::cin>>ided;
            g.test_remove_edge(ided);
        }

        if(key[KEY_V])
        {
            std::cout<<"saisir index sommet a effacer"<<std::endl;
            std::cin>>idv;
            g.remove_vertex(idv);
        }
        if(key[KEY_N])
        {
            std::cout<<"combien d'arete voulez vous saisir?"<<std::endl;
            std::cin>>val;

            for(int i=0; i<val; i++)
            {


                std::cout<<"saisir sommet depart"<<std::endl;
                std::cin>>som_dep;
                std::cout<<"saisir sommet d'arrivee"<<std::endl;
                std::cin>>som_arr;
                std::cout<<"saisir poids arete entre les deux"<<std::endl;
                std::cin>>poids;

                do
                {


                    std::cout<<"erreur le poids doit etre different de 0"<<std::endl;
                    std::cin>>poids;
                }
                while(poids==0);


                //std::cout<<g.get_index()<<std::endl;
                g.add_interfaced_edge(g.get_index(),som_dep,som_arr,poids);


            }
        }
    }
    g.save(idv, ided);
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


