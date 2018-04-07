#include "grman/grman.h"
#include <iostream>
#include <allegro.h>
//#include <allegro_native_dialog.h>

#include "graph.h"


int menu ()
{

    int selection;

    BITMAP *image = load_bitmap("picmenu.bmp",NULL);
    blit(image,screen,0,0,0,0, image->w, image->h);


   if (key[KEY_LEFT]
    {
    if (event.mouse.x >= MYGAME_MENU_X1 && event.mouse.x < MYGAME_MENU_X2 &&
        event.mouse.y >= MYGAME_MENU_Y1 && event.mouse.y < MYGAME_MENU_Y2)
    {
      selection = 1;
    }

        if (event.mouse.x >= MYGAME_MENU_X1 && event.mouse.x < MYGAME_MENU_X2 &&
        event.mouse.y >= MYGAME_MENU_Y1 && event.mouse.y < MYGAME_MENU_Y2)
    {
      selection = 2;
    }

        if (event.mouse.x >= MYGAME_MENU_X1 && event.mouse.x < MYGAME_MENU_X2 &&
        event.mouse.y >= MYGAME_MENU_Y1 && event.mouse.y < MYGAME_MENU_Y2)
    {
      selection = 3;
    }
  }
    return selection;
}

int main()
{
    int ided;
    int idv;
    int som_dep, som_arr, index, poids, x, y;
    std::string nom;
    int cap_port,rtm, nb_pop;
    int val;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
  std::cout<<"*************************bienvenue*****************************"<<std::endl;
        std::cout<<"Menu:\nAppuyez sur [e] pour effacer une arrete\nAppuyez sur [v] pour effacer un sommet"<<std::endl;
        std::cout<<"Appuyez sur [n] pour creer une arrete"<<std::endl;
        std::cout<<"Appuyez sur [b]pour creer un nouveau sommet"<<std::endl;
    while ( !key[KEY_ESC] )
    {

        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

     if(key[KEY_UP])
        {
        clear_bitmap(GraphInterface)
        }


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
        if(key[KEY_B])
        {
            std::cout<<"combien de sommets voulez vous saisir?"<<std::endl;
            std::cin>>val;

            for(int i=0; i<val; i++)
            {


                std::cout<<"saisir nombre de population"<<std::endl;
                std::cin>>nb_pop;
                std::cout<<"saisir coordonee selon x"<<std::endl;
                std::cin>>x;
                std::cout<<"saisir coordonee selon y"<<std::endl;
                std::cin>>y;
                std::cout<<"saisir le nom du sommet"<<std::endl;
                std::cin>>nom;
                nom=nom+".jpg";
                std::cout<<"saisir la capacite de portage"<<std::endl;
                std::cin>>cap_port;

                std::cout<<"saisir le rythme de croissance"<<std::endl;
                std::cin>>rtm;

                g.add_interfaced_vertex(g.get_index1(), nb_pop,x,y,nom,rtm,cap_port);
            }
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
                if(poids==0)
                {


                do
                {


                    std::cout<<"erreur le poids doit etre different de 0"<<std::endl;
                    std::cin>>poids;
                }
                while(poids==0);
                }


                //std::cout<<g.get_index()<<std::endl;
                g.add_interfaced_edge(g.get_index2(),som_dep,som_arr,poids);


            }
        }

    }
    g.save(idv, ided);
    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


