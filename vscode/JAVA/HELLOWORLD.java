import java.util.ArrayList;
import java.util.List;


public class HELLOWORLD {
  public static void main(String[] args) {
    List<String> list = List.of("aaa", "bbb", "ccc");
    System.out.println(list.toString());
  }

}

class Pair<T, K>{
  private T first;
  private K second;

  public Pair(T first, K second){
    this.first = first;
    this.second = second;
  }

  public T getFirst(){
    return first;
  }

  public K getSecond(){
    return second;
  }
}