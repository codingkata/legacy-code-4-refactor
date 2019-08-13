package legacy;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Direction {

	private static Direction instance;

	private static ArrayList<Character> index = new ArrayList<Character>();

	private static Map<Character, Integer> direction = new HashMap<Character, Integer>();

	public Direction() {
		index.add('N');
		index.add('E');
		index.add('S');
		index.add('W');
		direction.put('N', 1);
		direction.put('E', 1);
		direction.put('S', -1);
		direction.put('W', -1);
	}

	public static Direction getInstance() {
		if (instance == null) {
			instance = new Direction();
		}
		return instance;
	}

	public char turnTo(char faceTo, String LR) {
		String lr = LR.toUpperCase();
		int count = (lr.equals("L") ? -1 : 1);
		char new_faceTo = index.get((index.indexOf(faceTo) + count + 4) % 4);
		return new_faceTo;
	}

	public Position moveXY(char faceTo, Position pos) {
		if (index.indexOf(faceTo) % 2 == 1) {
			pos.setX(pos.getX() + direction.get(faceTo) <= 0 ? 0 : pos.getX()
					+ direction.get(faceTo));
		} else {
			pos.setY(pos.getY() + direction.get(faceTo) <= 0 ? 0 : pos.getY()
					+ direction.get(faceTo));
		}
		return pos;
	}

}