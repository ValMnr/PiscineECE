#include "grman/grman.h"
#include <iostream>
#include <allegro.h>
#include "grman/widget.h"
//#include <allegro_native_dialog.h>

#include "graph.h"

int main()
{
    int ided;
    int idv;
    int som_dep, som_arr, poids, x, y;
    std::string nom;
    int cap_port,rtm, nb_pop;
    int val;

    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    grman::Widget w;
//    Grman n;

    g.make_example();


    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
  std::cout<<"*************************bienvenue*****************************"<<std::endl;
    while ( !w.draw_bouton5()==1 )
    {

        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();




        if(w.draw_bouton1()==1)
        {
            std::cout<<"saisir index arete a supprimer"<<std::endl;
            std::cin>>ided;
            g.test_remove_edge(ided);
        }

        if(w.draw_bouton2()==1)
        {
            std::cout<<"saisir index sommet a effacer"<<std::endl;
            std::cin>>idv;
            g.remove_vertex(idv);
        }
        if(w.draw_bouton3()==1)
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






        if(w.draw_bouton4())
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
        if(w.draw_bouton6()==1)
        {

        }

    }
    g.save(idv, ided);
    grman::fermer_allegro();
    std::cout<<"a bientot :)"<<std::endl;

    return 0;
}
END_OF_MAIN();


