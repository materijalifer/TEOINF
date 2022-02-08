import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class edekoder {

	public edekoder() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param args
	 */
	public static void main(String[] args)
            throws IOException, IllegalArgumentException
    {
        if (args.length != 3) {
            throw new IllegalArgumentException ("UPORABA: java edekoder putanja_do_ulaza/zdekoderOut.txt "
                    + "putanja_do_koda/ekoderCode.txt putanja_do_odredista/odrediste_1.txt");
        }

        //U�itavanje iz datoteke zadane 0. parametrom
            File f = new File(args[0]);
            Scanner input = new Scanner( f );
            input.useDelimiter("");
        //Lista za spremanje znakova iz datoteke
            List<Integer> ulazniZnakovi = new ArrayList<Integer>();
        //�itanje i spremanje svakog znaka u ArrayList
            char znak;
            while (input.hasNext()) {
                znak = input.next().charAt(0);
                if (znak == '0') {
                    ulazniZnakovi.add(0);
                } else {
                    ulazniZnakovi.add(1);
                }
            }

        //U�itavanje iz datoteke zadane 1. parametrom
            File f2 = new File(args[1]);
            Scanner input2 = new Scanner( f2 );
            input2.useDelimiter("\r\n");
        //HashMap za spremanje sve iz ekoderCode.txt
            HashMap <String,String> ekoderCode = new HashMap<String, String>();
        //�itanje i spremanje svakog znaka u HashMap
            String str;
            String[] tokens;
            Integer najkraci = Integer.MAX_VALUE;
            Integer najdulji = 0;
            while (input2.hasNext()) {
                str = input2.next();
                tokens = str.split("=");
                ekoderCode.put(tokens[1], tokens[0]);

                for (int i = 0; i < tokens[1].length(); i++) {
                    if (tokens[1].length() > najdulji) {
                        najdulji = tokens[1].length();
                    }
                    if (tokens[1].length() < najkraci) {
                        najkraci = tokens[1].length();
                    }
                }
            }

        //Ispis u datoteku odrediste_1.txt odmah nakon dekodiranja
            FileWriter fstream = new FileWriter(args[2]);
            BufferedWriter out = new BufferedWriter(fstream);

        //Privremeni niz za �itanje znakova i dekodiranje simbola
            String niz = "";
            Integer brojac = 0;
            for (int i = 0; i < ulazniZnakovi.size(); i++) {
                //U svakoj iteraciji �itamo po jedan znak
                //System.out.println(niz);
                    niz += ulazniZnakovi.get(i);
                //Za dekodiranje duljina niza mora biti barem duljina najkra�eg koda u ekoderOut.txt
                    brojac++;
                    if ( brojac >= najkraci) {
                        //Dekodiranje ako je pro�itani niz dovoljan za dekodiranje
                        if (ekoderCode.containsKey(niz)) {
                            //Dekodirani zapis u datoteku
                                out.write(ekoderCode.get(niz));
                            //Resetiranje pro�itanog niza i broja�a za novo dekodiranje
                                niz = "";
                                brojac = 0;
                        }
                    }
                //Ako nije mogu�e dekodirati, ako je bila vi�estruka pogre�ka
                    if ( brojac > najdulji) {
                        //Zapis gre�ke u datoteku
                            out.write('#');
                        break;
                    }
            }
        //Ako je ostao pro�itani ne dekodirani niz onda je gre�ka
            if ( (niz.length() > 0) && (brojac <= najdulji) ) {
                for (int i = 0; i < niz.length(); i++) {
                    //Nije gre�ka ukoliko su sve nule, odnosno ukoliko je to onaj vi�ak dodan u zkoderu
                    if (niz.charAt(i) != '0') {
                        //Zapis gre�ke u datoteku
                            out.write('#');
                        break;
                    }
                }
            }

        //Zatvaranje pristupa datoteci odrediste_1.txt
            out.close();
	}

}