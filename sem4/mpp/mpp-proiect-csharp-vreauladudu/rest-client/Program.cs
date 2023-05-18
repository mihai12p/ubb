using mpp_proiect_csharp_vreauladudu.domain;

namespace restclient
{
    internal static class Program
    {
        private static HttpClient client = new HttpClient(new LoggingHandler(new HttpClientHandler()));
        private static string URL = "http://localhost:8080/moto/motorcycles";

        public static void Main(string[] args)
        {
            RunAsync().Wait();
        }

        static async Task RunAsync()
        {
            client.BaseAddress = new Uri(URL);
            client.DefaultRequestHeaders.Accept.Clear();
            client.DefaultRequestHeaders.Accept.Add(new System.Net.Http.Headers.MediaTypeWithQualityHeaderValue("application/json"));

            Motorcycle motorcycle = new Motorcycle();
            motorcycle.Brand = "HondaTESTREST_CSharp";
            motorcycle.Capacity = 125;


            Motorcycle result = await save(motorcycle);
            Console.WriteLine("Save motorcycle {0}", result);
            Motorcycle[] resultList = await findAll();
            foreach (Motorcycle m in resultList)
            {
                Console.WriteLine(m);
            }

            result = await find(result.Id);
            Console.WriteLine("Find motorcycle {0}", result);

            motorcycle.Brand = "MOTOUPDATE";
            result = await update(motorcycle, result.Id);
            Console.WriteLine("Update motorcycle {0}", result);

            await remove(result.Id);
        }

        static async Task<Motorcycle[]?> findAll()
        {
            Motorcycle[]? result = null;

            HttpResponseMessage response = await client.GetAsync(URL);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Motorcycle[]>();
            }
            return result;
        }

        static async Task<Motorcycle?> find(int id)
        {
            Motorcycle? result = null;

            HttpResponseMessage response = await client.GetAsync(URL + "/" + id.ToString());
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Motorcycle>();
            }
            return result;
        }

        static async Task<Motorcycle?> save(Motorcycle motorcycle)
        {
            Motorcycle? result = null;

            HttpResponseMessage response = await client.PostAsJsonAsync(URL, motorcycle);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Motorcycle>();
                motorcycle.Id = result.Id;
            }
            return result;
        }

        static async Task<Motorcycle?> update(Motorcycle motorcycle, int id)
        {
            Motorcycle? result = null;

            HttpResponseMessage response = await client.PutAsJsonAsync(URL + "/" + id.ToString(), motorcycle);
            if (response.IsSuccessStatusCode)
            {
                result = await response.Content.ReadAsAsync<Motorcycle>();
            }
            return result;
        }

        static async Task remove(int id)
        {
            await client.DeleteAsync(URL + "/" + id.ToString());
        }
    }

    internal class LoggingHandler : DelegatingHandler
    {
        public LoggingHandler(HttpMessageHandler handler) : base(handler) { }

        protected override async Task<HttpResponseMessage> SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
        {
            Console.WriteLine("Request:");
            Console.WriteLine(request.ToString());
            if (request.Content != null)
            {
                Console.WriteLine(await request.Content.ReadAsStringAsync());
            }
            Console.WriteLine();

            HttpResponseMessage response = await base.SendAsync(request, cancellationToken);

            Console.WriteLine("Response:");
            Console.WriteLine(response.ToString());
            if (response.Content != null)
            {
                Console.WriteLine(await response.Content.ReadAsStringAsync());
            }
            Console.WriteLine();

            return response;
        }
    }
}