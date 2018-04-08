#include "grman/grman.h"
#include <iostream>
#include <allegro.h>
//#include <allegro_native_dialog.h>

#include "graph.h"

#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


int menu ()
{


    int selection=0;
    bool click;
    BITMAP *image = load_bitmap("pics/picmenu.bmp",NULL);
    blit(image, screen,0,0,0,0,800,600);
    click=false;


while(!click) {
    if (mouse_b & 1)
    {
        click=true;
        if (mouse_x >= 193 && mouse_x < 570 &&
                mouse_y >= 240 && mouse_y < 327)
        {
            selection = 1;
        }

        if(        mouse_x >= 190 && mouse_x < 570 &&
                   mouse_y >= 349 && mouse_y < 420)
        {
            selection = 2;
        }

        if (        mouse_x >= 190 && mouse_x < 570  &&
                    mouse_y >= 435 && mouse_y < 500)
        {
            selection = 3;
        }

    }
}
    return selection;

}

bool boucle_de_jeu(Graph *g)
{
    grman::Widget w;
    g->make_example();
    int idv;
    int ided;



    while ( !w.draw_bouton5()==1 )
    {



        if(w.draw_bouton6()==1)  /// Actualisation de la population
        {
           // w.draw_bouton1()==0;
            g->updatePop();
            system("cls");

        }

        // if (key[KEY_UP])  /// Actualisation de la population
        //  { delete *GraphInterface g.graphin}

        if(w.draw_bouton1()==1) ///Suppression edge
        {
            int ided;
            std::cout<<"saisir index arete a supprimer"<<std::endl;
            std::cin>>ided;
            g->test_remove_edge(ided);
        }

        /*     if(key[KEY_UP]) ///CFC
             {
             g->remplissage();
             g->printSCCs();
        }
        */
        if(w.draw_bouton3()==1)
        {
            int val, nb_pop,x,y,cap_port,rtm;
            std::string nom;
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
                int idx =g->getVertices().size()+1;
                g->add_interfaced_vertex(idx, nb_pop,x,y,nom,rtm,cap_port);
            }
        }





        if(w.draw_bouton2()==1) ///Suppression vertex
        {
            int idv;
            std::cout<<"saisir index sommet a effacer"<<std::endl;
            std::cin>>idv;
            g->remove_vertex(idv);
        }

        if(w.draw_bouton4()==1) ///Ajout d'edge
        {
            int val;
            std::cout<<"combien d'arete voulez vous saisir?"<<std::endl;
            std::cin>>val;

            for(int i=0; i<val; i++)
            {
                int som_dep,som_arr,poids;
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
                g->add_interfaced_edge(g->get_index(),som_dep,som_arr,poids);


            }
        }
        /*
        */
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g->update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();







    }

    // g->second.getInter buf_afficher_page();
    return false;
}

void printCom()
{

    std::cout<<"****************************************"<<std::endl;
    std::cout<<"Presser : "<<std::endl;

    std::cout<<"- Q pour voir evolution de la population"<<std::endl;

    std::cout<<"- E pour supprimer arete"<<std::endl;

    std::cout<<"- N pour ajouter arrete"<<std::endl;

    std::cout<<"- ESC pour revenir au menu"<<std::endl;



}

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nC:\Users\Valentin\Desktop\Last version\graph_lib.cbpom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )



    while ( !key[KEY_ESC] )
    {

        bool selection = false ;
        int chx;

        do
        {


            chx= menu();
            std::cout<<"ok2"<<std::endl;

            Graph *crt_gr;

            crt_gr = new Graph(chx);


            std::cout<<"ok3"<<std::endl;

            // Graph gcrt(chx);

            printCom();

            //        grman::Widget w;

            selection = boucle_de_jeu(crt_gr);
            //Graph *g = new Graph(chx);
            //Graph g(chx);

        }
        while (selection==false);

        std::cout<<"ok5"<<std::endl;


    }

    //g.save2();
//    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


