import cpp_component.*;

public class Java_applet
    {
    public static void main(String args[])
        {
        IStock stock = (IStock) new CStock();
        stock.getCommission();
        }
    }
