/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Expected True:");
	   System.out.println("http://www.google.com");
	   System.out.println(urlVal.isValid("http://www.google.com"));
	   System.out.println("http://www.google.org");
	   System.out.println(urlVal.isValid("http://www.google.org"));
	   System.out.println("http://www.google.co.uk");
	   System.out.println(urlVal.isValid("http://www.google.co.uk"));
	   System.out.println("http://www.google.com:1");
	   System.out.println(urlVal.isValid("http://www.google.com:1"));	   
	   System.out.println("http://www.google.com:11");
	   System.out.println(urlVal.isValid("http://www.google.com:11"));
	   System.out.println("http://www.google.com:111");
	   System.out.println(urlVal.isValid("http://www.google.com:111"));
	   System.out.println("http://www.google.com:1111");
	   System.out.println(urlVal.isValid("http://www.google.com:1111"));
	   System.out.println("http://www.google.com:11111");
	   System.out.println(urlVal.isValid("http://www.google.com:11111"));
	   System.out.println("https://www.google.com");
	   System.out.println(urlVal.isValid("https://www.google.com"));	   
	   System.out.println("ftp://www.google.com");
	   System.out.println(urlVal.isValid("ftp://www.google.com"));
	   System.out.println("www.google.com");
	   System.out.println(urlVal.isValid("www.google.com"));
	   System.out.println("http://wwwwwwwwwwwwwwwww.google.com");
	   System.out.println(urlVal.isValid("http://wwwwwwwwwwwwwwwww.google.com"));
	   System.out.println("http://localhost");
	   System.out.println(urlVal.isValid("http://localhost"));
	   System.out.println("http://www.google.com/maps/");
	   System.out.println(urlVal.isValid("http://www.google.com/maps/"));
	   System.out.println("http://www.google.com/maps/asia");
	   System.out.println(urlVal.isValid("http://www.google.com/maps/asia"));
	   System.out.println("http://google.com?test=value");
	   System.out.println(urlVal.isValid("http://google.com?test=value"));
	   System.out.println("http://google.com?test=value&thing=stuff");
	   System.out.println(urlVal.isValid("http://google.com?test=value&thing=stuff"));
	   
	   System.out.println("\nExpected False:");
	   System.out.println("http://www.google.bob");
	   System.out.println(urlVal.isValid("http://www.google.bob"));
	   System.out.println("http://www.google");
	   System.out.println(urlVal.isValid("http://www.google"));
	   System.out.println("http://www.google.com:111111");
	   System.out.println(urlVal.isValid("http://www.google.com:111111"));
	   System.out.println("http://www.google.com:-1");
	   System.out.println(urlVal.isValid("http://www.google.com:-1"));
	   System.out.println("http://www.google.com:");
	   System.out.println(urlVal.isValid("http://www.google.com:"));
	   System.out.println("http://www.google.com:1a");
	   System.out.println(urlVal.isValid("http://www.google.com:a"));
	   System.out.println("http:/www.google.com");
	   System.out.println(urlVal.isValid("http:/www.google.com"));
	   System.out.println("http:www.google.com");
	   System.out.println(urlVal.isValid("http:www.google.com"));
	   System.out.println("://www.google.com");
	   System.out.println(urlVal.isValid("://www.google.com"));
	   System.out.println("http://www.google!!!!!.com");
	   System.out.println(urlVal.isValid("http://www.google!!!!!.com"));
	   System.out.println("http://www.google.com/^^^^^^^/");
	   System.out.println(urlVal.isValid("http://www.google.com/^^^^^^^/"));
	   System.out.println("http://256.256.256.256");
	   System.out.println(urlVal.isValid("http://256.256.256.256"));
	   System.out.println("http://999.999.999.999");
	   System.out.println(urlVal.isValid("http://999.999.999.999"));
	   
	   
	   
   }
   
   
   public void testYourFirstPartition() {
	   boolean result;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validScheme = {"", "http://", "h3t://"};
	   String[] invalidScheme = {"http:/", "://", "123http://", " "};
	   String testUrl;
	   String validAuth = "www.google.com";
	   
	   System.out.println("Scheme Partition Test\n");
	   System.out.println("Expected True:");
	   for(int i = 0; i < validScheme.length; i++){
		   testUrl = validScheme[i] + validAuth;
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\nExpected False:");
	   for(int i = 0; i < invalidScheme.length; i++){
		   testUrl = invalidScheme[i] + validAuth;
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\n");
   }
   
   public void testYourSecondPartition() {
	   boolean result;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validAuth = {"www.google.com", "0.0.0.0", "255.255.255.255", "localhost", "google1.com","www.google.co.uk"};
	   String[] invalidAuth = {"256.256.256.256", "255.255.255.255.255", "www.google", "", "www.goo!gle.com", ""};
	   String testUrl;
	   String validScheme = "http://";
	   
	   System.out.println("Authority Partition Test\n");
	   System.out.println("Expected True:");
	   for(int i = 0; i < validAuth.length; i++){
		   testUrl = validScheme + validAuth[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\nExpected False:");
	   for(int i = 0; i < invalidAuth.length; i++){
		   testUrl = validScheme + invalidAuth[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\n");
   }
   
   public void testYourThirdPartition() {
	   boolean result;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validPort = {"", ":0", ":65535"};
	   String[] invalidPort = {" :", ":", ":65536", ":-1", ":1port", "1"};
	   String testUrl;
	   String validUrl = "http://www.google.com";
	   
	   System.out.println("Port Partition Test\n");
	   System.out.println("Expected True:");
	   for(int i = 0; i < validPort.length; i++){
		   testUrl = validUrl + validPort[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\nExpected False:");
	   for(int i = 0; i < invalidPort.length; i++){
		   testUrl = validUrl + invalidPort[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\n");
   }

   public void testYourFourthPartition() {
	   boolean result;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validPath = {"/", "/path1/folder1/file1.java", "/1"};
	   String[] invalidPath = {" /path", "/ path", "path", "//path", "/p^th", "/.."};
	   String testUrl;
	   String validUrl = "http://www.google.com:0";

	   System.out.println("Path Partition Test\n");
	   System.out.println("Expected True:");
	   for(int i = 0; i < validPath.length; i++){
		   testUrl = validUrl + validPath[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\nExpected False:");
	   for(int i = 0; i < invalidPath.length; i++){
		   testUrl = validUrl + invalidPath[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\n");
   }

   public void testYourFifthPartition() {
	   boolean result;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String[] validQuery = {"?user1=name1", "?user1=name1&pass1=word1"};
	   String[] invalidQuery = {"?user=", "??user=name", " ?user=name"};
	   String testUrl;
	   String validUrl = "http://www.google.com:0/path/";

	   System.out.println("Query Partition Test\n");
	   System.out.println("Expected True:");
	   for(int i = 0; i < validQuery.length; i++){
		   testUrl = validUrl + validQuery[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\nExpected False:");
	   for(int i = 0; i < invalidQuery.length; i++){
		   testUrl = validUrl + invalidQuery[i];
		   result = urlVal.isValid(testUrl);
		   System.out.println(testUrl + "\n" + result);
	   }
	   
	   System.out.println("\n");

   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
		   boolean result;
	   boolean expected = true;
	   String schemeString;
	   String authString;
	   String portString;
	   String pathString;
	   String queryString;
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   ResultPair[] Schemes = {new ResultPair("http://", true), new ResultPair("https://", true), new ResultPair("h3t://", true), new ResultPair("ftp://", true), new ResultPair(":\\", false), new ResultPair("http", false), new ResultPair("http:", false)};
	   ResultPair[] Authorities = {new ResultPair("www.amazon.com", true), new ResultPair("go.com", true), new ResultPair("0.0.0.0", true), new ResultPair("10.10.10.10", true), new ResultPair("255.255.255.255", true), new ResultPair("www.amazon.co.uk", true), new ResultPair("go.au", true), new ResultPair("256.256.256.256", false), new ResultPair("999.999.999.999", false), new ResultPair("1000.1000.1000.1000", false), new ResultPair("-1.1.1.1", false), new ResultPair("1.1.1.1.1", false)};
	   ResultPair[] Ports = {new ResultPair(":80", true), new ResultPair(":0", true), new ResultPair(":65535", true), new ResultPair(":999", true), new ResultPair(":1000", true), new ResultPair(":65536", false), new ResultPair(":100000", false), new ResultPair(":-1", false), new ResultPair("", true)};
	   ResultPair[] Paths = {new ResultPair("/path1", true), new ResultPair("/path", true), new ResultPair("", true), new ResultPair("/path/test", true), new ResultPair("/...", false), new ResultPair("/path//test", false)};
	   ResultPair[] Queries = {new ResultPair("?foo=bar", true), new ResultPair("?foo=bar&bar=baz", true), new ResultPair("", true), new ResultPair("?foo=bar&bar=baz&baz=foo", true)};
	   
	   System.out.println("\n");
	   for(int i = 0; i < Schemes.length; i++) {
		   schemeString = Schemes[i].item;
		   		   
		   for (int j = 0; j < Authorities.length; j++) {
			   authString = schemeString + Authorities[j].item;
			   
			   for(int k = 0; k < Ports.length; k++) {
				   portString = authString + Ports[k].item;
				   
				   for (int m = 0; m < Paths.length; m++) {
					   pathString = portString + Paths[m].item;
					   
					   for (int n = 0; n < Queries.length; n++) {
						   queryString = pathString + Queries[n].item;
						   expected = Schemes[i].valid && Authorities[j].valid && Ports[k].valid && Paths[m].valid && Queries[n].valid;
						   result = urlVal.isValid(queryString);
						   if (result != expected) {
							   System.out.println(queryString + "\nexpected: " + expected + "\nresult: " + result);
						   }
					   }
				   }
			   }
		   }
	   }   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
