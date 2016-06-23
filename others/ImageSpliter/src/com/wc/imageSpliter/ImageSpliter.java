package com.wc.imageSpliter;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;

public class ImageSpliter {

	public static void main(String[] args) {
		ArrayList<BufferedImage> bufferedImages = ImageSpliter.cutImage("C:\\test.png", 2, 2);
		System.out.println("" + bufferedImages.size());
		String filePathName = "c:";
		int number = 0;
		String formatString = "jpg";
		for(BufferedImage bufferedImage : bufferedImages){
			number++;
			File file = new File(filePathName + "\\test" + number + "." + formatString);
			//System.out.println("File :" + file);
			try {
				ImageIO.write(bufferedImage, formatString, file);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public static ArrayList<BufferedImage> cutImage(String filepath,  int nrows, int ncols) {
		int nums = nrows * ncols;
		ArrayList<BufferedImage> bufferedImages = new ArrayList<BufferedImage>();
		try{
			BufferedImage bufferedImage = ImageIO.read(new File(filepath));
			int lw = bufferedImage.getWidth() / ncols;
			int lh = bufferedImage.getHeight()/ nrows;
			for(int i = 0; i < nums; ++i){
				BufferedImage img = bufferedImage.getSubimage(i % ncols * lw, i / ncols * lh, lw, lh);
				bufferedImages.add(img);
			}
			return bufferedImages;
		}catch(IOException e){
			e.printStackTrace();
		}
		return bufferedImages;
	}

}
