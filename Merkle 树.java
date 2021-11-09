import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class Merkle {

    public static void main(String[] args) {
        // 用户输入的数据个数
        int n;
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        // 规整到2的整数次幂
        int e = 0;
        while (n > (1 << e)) {
            e += 1;
        }
        int nn = (1 << e);
        // 存储数据
        int[] data = new int[nn + 1];
        for (int i = 1 ; i <= n; i += 1) {
            data[i] = in.nextInt();
        }
        // 构造Merkel 树存储数组
        int totalNodes = (1 << (e + 1)) - 1;
        String[] merkleTree = new String[totalNodes + 1];
        // 构造底层哈希
        int ptr = 1;
        for (int i = totalNodes - nn + 1; i <= totalNodes; i += 1) {
            merkleTree[i] = encrypt("" + data[ptr]);
            ptr += 1;
        }
        // 自低向上计算hash 值
        int left = totalNodes - nn + 1;
        int right = totalNodes;
        // 到merkle 的根节点停止hash 计算
        while (left != 1) {
            for (int i = left; i <= right; i += 2) {
                merkleTree[i / 2] = encrypt(merkleTree[i] + merkleTree[i + 1]);
            }
            left >>= 1;
            right >>= 1;
        }
        System.out.println("finger_print 为：" + merkleTree[1]);
    }

    // SHA-256 加密入参
    public static String encrypt(String value) {
        if (value == null) {
            return "";
        }
        MessageDigest messageDigest = null;
        byte[] buf = null;
        try {
            messageDigest = MessageDigest.getInstance("sha-256");
            buf = value.getBytes(StandardCharsets.UTF_8);
            buf = messageDigest.digest(buf);
        } catch (NoSuchAlgorithmException e) {

        }
        StringBuffer result = new StringBuffer();
        for (int i = 0; buf != null && i < buf.length; i += 1) {
            result.append(String.format("%02x", buf[i]));
        }
        return result.toString();
    }

}
