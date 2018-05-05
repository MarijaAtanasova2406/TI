import java.io.*;
import static java.lang.System.*;

public class Entropy {

    public static void main(String[] args) throws IOException {
        out.println("Внесете збор или реченица ");

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String signal = br.readLine();

        out.println("Внесете буква или пар од букви");
        String x = br.readLine();
        int counter = 0;
        if (x.length() == 1){
            for( int i=0; i<signal.length(); i++ ) {
                if( signal.charAt(i) == x.charAt(0) ) {
                    counter++;
                }
            }
            double variable = signal.length();
            char finalX = x.charAt(0);
            double s = signal.chars().filter(num -> num == finalX).count();
            double entropija = s/ variable ;
            out.println("Буквата " + x + " се појавува " + counter + " пати ");
            out.println("Фрекфенцијата на буквата  " + x + "  " + s / variable);
            out.println("Ентропијата на буквата " + ((-1*entropija*Math.log(entropija))));
        }
        if (x.length() == 2 ){
            int lastIndex = 0;
            while(lastIndex != -1){
                lastIndex = signal.indexOf(x,lastIndex);
                if(lastIndex != -1){
                    counter ++;
                    lastIndex += x.length();
                }
            }
            double x_2  = count(signal,x);
            out.println("Парот од букви " + x + " се појавува " + counter + " пати ");
            out.println("Фрекфенцијата на буквите  " + x + "  " +x_2/signal.length());
            double EnthropyPair = x_2/signal.length();
            out.println("Ентропијата на парот изнесува  " + x + "  "+ (-1*EnthropyPair*Math.log(EnthropyPair)));
        }
        if (x.length()>2 ) {
            out.println("Внесовте повеќе од 2 букви, обидете се повторно");
            return;
        }
    }

    public static double count(String text, String find) {
        int index = 0, count = 0, length = find.length();
        while( (index = text.indexOf(find, index)) != -1 ) {
            index += length; count++;
        }
        return count;
    }

}
