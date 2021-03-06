describe "downpour connections" do

  before(:each) do
    @status = Downpour.create
    @user = ENV["USER"]
    @password = ""
    @database = "test"
  end

  shared_examples_for "a working downpour connection" do
    it "should count records" do
      results = @connection.query "select * from Test1"
      results.row_count.should == 3
    end

    it "should read a row" do
      results = @connection.query "select * from Test1"
      results.next_row.should == ["foo"]
    end

    it "should be used concurrently" do
      query = @status.add_query(@connection, "select * from Test1")
      @status.run_all!
      query.result.next_row.should == ["foo"]
    end
  end

  context "over drizzle tcp protocol" do
    it "should have default port set" do
      connection = @status.add_tcp_connection('localhost', @user, @password, @database)
      connection.port.should == 4427
    end

    context "connection sanity" do
      before(:each) do
        @connection = @status.add_tcp_connection('localhost', @user, @password, @database)
      end

      it_should_behave_like "a working downpour connection"
    end
  end

  context "over mysql tcp protocol" do
    it "should have default port set" do
      connection = @status.add_mysql_tcp_connection('localhost', @user, @password, @database)
      connection.port.should == 3306
    end

    context "connection sanity" do
      before(:each) do
        # connect to drizzle over a mysql db
        @connection = @status.add_mysql_tcp_connection('localhost', @user, @password, @database, 4427)
      end

      it_should_behave_like "a working downpour connection"
    end
  end
end
