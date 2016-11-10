
public class test {
    public static void main(String[] args) {
        int[] arr = new int[5];
        for (int k = 0; k < arr.length; k++) {
            arr[k] = k;
        }   
    
        System.out.print("Before: ");
        System.out.println(arr[0]);

        modifyArray(arr);
        System.out.print("After: ");
        System.out.println(arr[0]);


    }   

    static void modifyArray(int[] array) {
        array[0] = 999;
    }
}
