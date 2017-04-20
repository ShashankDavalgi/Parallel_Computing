/*

WordCount program using MapReduce:
Mapper
Reducer
Main_Function

*/

import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

/* MAPPER */

public class WordCount {

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, IntWritable>{

	//hadoop supported data types:'IntWritable'
	   
    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();

	//map method that performs the tokenizer job and framing the initial key value pairs
	
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
						
	//taking one line at a time and tokenizing the same					
						
      StringTokenizer itr = new StringTokenizer(value.toString());
	  
	//iterating through all the words available in that line and forming the key value pair
	
      while (itr.hasMoreTokens()) {
        word.set(itr.nextToken());
		
	//sending to output collector which in turn passes the same to reducer
        context.write(word, one);
      }
    }
  }

  /* REDUCER */
  
  public static class IntSumReducer
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

	/* reduce method accepts the Key Value pairs from mappers,
	do the aggregation based on keys and produce the final out put*/
	
    public void reduce(Text key, Iterable<IntWritable> values,
                       Context context
                       ) throws IOException, InterruptedException {
      int sum = 0;
	  
	  /*iterates through all the values available with a key and add them together and give the
            final result as the key and sum of its values*/
	  
      for (IntWritable val : values) {
        sum += val.get();
      }
      result.set(sum);
      context.write(key, result);
    }
  }
  
  /* Main Function */

  public static void main(String[] args) throws Exception {
	  
	  //creating a JobConf object and assigning a job name for identification purposes
	  
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "word count");
    job.setJarByClass(WordCount.class);
	
	//Providing the mapper and reducer class names
	
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);
    job.setReducerClass(IntSumReducer.class);
	
	//Setting configuration object with the Data Type of output Key and Value
	
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
	
	//the hdfs input and output directory to be fetched from the command line
	
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}
