package legacy;

import java.util.*;

public class Main {
	public static void main(String[] args) {
		List<String> cmd = new ArrayList<String>();
		cmd.add("5 5");
		cmd.add("1 2 N");
		cmd.add("LMLMLMLMM");
		cmd.add("3 3 E");
		cmd.add("MM");
		String result = MarsCarRunning(cmd);
		System.out.print(result);
	}

	public static String MarsCarRunning(List<String> cmd) {
		String resultInfo = "";
		if (cmd.size() % 2 != 1) {
			return "error cmd...";
		}
		Direction direction = Direction.getInstance();
		List<Detector> directionList = new ArrayList<Detector>();
		String[] maxXY = cmd.get(0).split(" ");
		Position maxPos = new Position(maxXY[0].trim(), maxXY[1].trim());
		for (int i = 1; i < cmd.size(); i += 2) {
			String[] tmp = cmd.get(i).split(" ");
			Detector detector = new Detector(tmp[2].toUpperCase().charAt(0),new Position(tmp[0], tmp[1]), cmd.get(i + 1),new Position(String.valueOf(maxPos.getX()), String.valueOf(maxPos.getY())));
			detector.excuteCMD(direction);
			detector.getPos().setX(detector.getPos().getX() <= maxPos.getX() ? detector.getPos().getX() : maxPos.getX());
			detector.getPos().setY(detector.getPos().getY() <= maxPos.getY() ? detector.getPos().getY() : maxPos.getY());
			directionList.add(detector);
		}
		for (int i = 0; i < directionList.size(); i++) {
			resultInfo += directionList.get(i).toString();
		}
		return resultInfo;
	}

}
