//Scanner

Scanner in=new Scanner(new FileReader("asdf"));
PrintWriter pw=new PrintWriter(new Filewriter("out"));
boolean       in.hasNext();
String        in.next();
BigDecimal    in.nextBigDecimal();
BigInteger    in.nextBigInteger();
BigInteger    in.nextBigInteger(int radix);
double        in.nextDouble();
int           in.nextInt();
int           in.nextInt(int radix);
String        in.nextLine();
long          in.nextLong();
long          in.nextLong(int radix);
short         in.nextShort();
short         in.nextShort(int radix);
int           in.radix(); //Returns this scanner's default radix.
Scanner       in.useRadix(int radix);// Sets this scanner's default radix to the specified radix.
void          in.close();//Closes this scanner.

//String

char          str.charAt(int index);
int           str.compareTo(String anotherString); // <0 if less. ==0 if equal. >0 if greater.
int           str.compareToIgnoreCase(String str);
String        str.concat(String str);
boolean       str.contains(CharSequence s);
boolean       str.endsWith(String suffix);
boolean       str.startsWith(String preffix);
boolean       str.startsWith(String preffix,int toffset);
int           str.hashCode();
int           str.indexOf(int ch);
int           str.indexOf(int ch,int fromIndex);
int           str.indexOf(String str);
int           str.indexOf(String str,int fromIndex);
int           str.lastIndexOf(int ch);
int           str.lastIndexOf(int ch,int fromIndex);
//(ry
int           str.length();
String        str.substring(int beginIndex);
String        str.substring(int beginIndex,int endIndex);
String        str.toLowerCase();
String        str.toUpperCase();
String        str.trim();// Returns a copy of the string, with leading and trailing whitespace omitted.

//StringBuilder
StringBuilder str.insert(int offset,...);
StringBuilder str.reverse();
void          str.setCharAt(int index,int ch);

//BigInteger
compareTo(); equals(); doubleValue(); longValue(); hashCode(); toString(); toString(int radix); max(); min(); mod(); modPow(BigInteger exp,BigInteger m); nextProbablePrime(); pow();
andNot(); and(); xor(); not(); or(); getLowestSetBit(); bitCount(); bitLength(); setBig(int n); shiftLeft(int n); shiftRight(int n);
add(); divide(); divideAndRemainder(); remainder(); multiply(); subtract(); gcd(); abs(); signum(); negate();

//BigDecimal
movePointLeft(); movePointRight(); precision(); stripTrailingZeros(); toBigInteger(); toPlainString();


//sort
class pii implements Comparable
{
    public int a,b;
    public int compareTo(Object i)
    {
        pii c=(pii)i;
        return a==c.a?c.b-b:c.a-a;
    }
}

class Main
{
    public static void main(String[] args)
    {
        pii[] the=new pii[2];
        the[0]=new pii();
        the[1]=new pii();
        the[0].a=1;
        the[0].b=1;
        the[1].a=1;
        the[1].b=2;
        Arrays.sort(the);
        for(int i=0;i<2;++i)
            System.out.printf("%d %d\n",the[i].a,the[i].b);
    }
}
